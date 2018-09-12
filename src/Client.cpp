#include "collabclient/Client.h"

#include <cassert>
#include <thread>
#include <sstream>
#include <string> // For operation buffer
#include <zmq.hpp> // For ZMQ socket options

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/messaging/Message.h"
#include "collabcommon/messaging/MessageList.h"
#include "collabcommon/network/ZMQSocket.h"
#include "collabcommon/utils/constants.h"

namespace collab {


// Local variables: prefixed with l_
static bool             l_isListeningSUB    = false;
static ZMQSocket*       l_socketREQ         = nullptr;
static ZMQSocket*       l_socketSUB         = nullptr;
static MessageFactory&  l_msgFactory        = MessageFactory::getInstance();


// Listen incoming RoomOperation messages
static void listenSocketSUB(CollabData* data) {
    assert(data != nullptr);
    assert(l_isListeningSUB == true);

    while(l_isListeningSUB) {
        Message* received = l_socketSUB->receiveMessage();
        if(received->getType() != MessageFactory::MSG_ROOM_OPERATION) {
            continue;
        }
        assert(data != nullptr);

        // TODO Add userID and roomID check etc
        MsgRoomOperation* msg = static_cast<MsgRoomOperation*>(received);
        int operationID = msg->getOpTypeID();
        const std::string& buffer = msg->getOperationBuffer();
        data->applyExternOperation(operationID, buffer);

        l_msgFactory.freeMessage(received);
    }
}

// Run the thread that listen to any operation comming from others over network.
static void startThreadSUB(int dataID, CollabData* data) {
    assert(l_isListeningSUB == false);
    assert(l_socketSUB != nullptr);
    assert(data != nullptr);

    // TODO tmp (Accept everything for now)
    // TODO: Check if the subscribe actually work (I'm not sure).
    // Unsubscribe all previous subsciption
    const char* filter = "";
    l_socketSUB->setsockopt(ZMQ_UNSUBSCRIBE, "", strlen(""));
    l_socketSUB->setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    if(l_isListeningSUB == true) { return; }
    l_isListeningSUB = true;

    std::thread(listenSocketSUB, data).detach();
}

static void stopThreadSUB() {
    l_isListeningSUB = false;
    // TODO: this actuall won't stop the current locked receiveMessage!
    // Panda! You need to figure out how to interrup this function.
    // For now, we will probably get a segfault or some horrible things like this.
}


Client::Client() {
    ZMQSocketConfig configREQ = { ZMQ_REQ, &(MessageFactory::getInstance()) };
    ZMQSocketConfig configSUB = { ZMQ_SUB, &(MessageFactory::getInstance()) };

    l_socketREQ = new ZMQSocket(configREQ);
    l_socketSUB = new ZMQSocket(configSUB);

    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);
}

Client::~Client() {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    this->leaveData();
    this->disconnect();

    delete l_socketREQ;
    delete l_socketSUB;
    l_socketREQ = nullptr;
    l_socketSUB = nullptr;
}

bool Client::connect(const char* ip, const int port) {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    if(this->isConnected()) { return false; }
    l_socketREQ->connect(ip, port);
    l_socketSUB->connect(ip, COLLAB_SOCKET_SUB_PORT);

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_CONNECTION_REQUEST);
    assert(m != nullptr);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CONNECTION_SUCCESS) {
        l_msgFactory.freeMessage(m);
        this->disconnect();
        return false;
    }

    _userID = static_cast<MsgConnectionSuccess*>(m)->getUserID();

    l_msgFactory.freeMessage(m);

    return true;
}

bool Client::disconnect() {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    if(this->isDataLoaded()) {
        this->leaveData();
    }

    if(!this->isConnected()) {
        return false;
    }

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_DISCONNECT_REQUEST);
    static_cast<MsgDisconnectRequest*>(m)->setUserID(_userID);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_DISCONNECT_SUCCESS) {
        l_msgFactory.freeMessage(m);
        return false;
    }

    _userID = -1;

    l_msgFactory.freeMessage(m);

    l_socketREQ->disconnect();
    l_socketSUB->disconnect();

    return true;
}

bool Client::createData(CollabData* data) {
    assert(data != nullptr);
    if(!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_CREA_DATA_REQUEST);
    static_cast<MsgCreaDataRequest*>(m)->setUserID(_userID);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CREA_DATA_SUCCESS) {
        l_msgFactory.freeMessage(m);
        return false;
    }

    _data = data;
    _dataID = static_cast<MsgCreaDataSuccess*>(m)->getDataID();

    l_msgFactory.freeMessage(m);

    assert(_data != nullptr);
    assert(_dataID != -1);

    data->setOperationBroadcaster(*this);
    startThreadSUB(_dataID, _data);

    return true;
}

bool Client::joinData(CollabData* data, unsigned int dataID) {
    assert(data != nullptr);
    assert(dataID > -1);
    if(!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_JOIN_DATA_REQUEST);
    static_cast<MsgJoinDataRequest*>(m)->setUserID(_userID);
    static_cast<MsgJoinDataRequest*>(m)->setDataID(dataID);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_JOIN_DATA_SUCCESS) {
        l_msgFactory.freeMessage(m);
        return false;
    }

    l_msgFactory.freeMessage(m);

    _dataID = dataID;
    _data = data;

    data->setOperationBroadcaster(*this);
    startThreadSUB(_dataID, _data);

    return true;
}

bool Client::leaveData() {
    if(!this->isConnected() || !this->isDataLoaded()) {
        return false;
    }

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_LEAVE_DATA_REQUEST);
    static_cast<MsgLeaveDataRequest*>(m)->setUserID(_userID);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_LEAVE_DATA_SUCCESS) {
        l_msgFactory.freeMessage(m);
        return false;
    }

    stopThreadSUB();

    _dataID = -1;
    _data->removeOperationBroadcaster();
    _data = nullptr;

    l_msgFactory.freeMessage(m);

    return true;
}

bool Client::isUgly() const {
    if(!this->isConnected()) {
        return true;
    }

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_UGLY);
    static_cast<MsgUgly*>(m)->setUserID(_userID);
    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_UGLY) {
        l_msgFactory.freeMessage(m);
        return false;
    }

    bool isUgly = static_cast<MsgUgly*>(m)->getResponse();

    l_msgFactory.freeMessage(m);

    return isUgly;
}

// DevNote: remind: this is for op done by the local user.
void Client::onOperation(const Operation& op) {
    if(!this->isConnected() || !this->isDataLoaded()) {
        assert(false); // Should not append (Internal error)
        return;
    }

    std::stringstream opBuffer;
    op.serialize(opBuffer);

    Message* m = l_msgFactory.newMessage(MessageFactory::MSG_ROOM_OPERATION);
    static_cast<MsgRoomOperation*>(m)->setRoomID(_dataID);
    static_cast<MsgRoomOperation*>(m)->setUserID(_userID);
    static_cast<MsgRoomOperation*>(m)->setOpTypeID(op.getType());
    static_cast<MsgRoomOperation*>(m)->setOperationBuffer(opBuffer.str());

    l_socketREQ->sendMessage(*m);
    l_msgFactory.freeMessage(m);

    m = l_socketREQ->receiveMessage();
    if(m->getType() != MessageFactory::MSG_EMPTY) {
        l_msgFactory.freeMessage(m);
        return;
    }

    l_msgFactory.freeMessage(m);
}


} // End namespace


