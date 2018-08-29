#include "collabclient/Client.h"

#include <cassert>

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/messaging/Message.h"
#include "collabcommon/messaging/MessageList.h"
#include "collabcommon/network/ZMQSocket.h"

namespace collab {


static ZMQSocket* local_socket = nullptr;
static MessageFactory& msgFactory = MessageFactory::getInstance();


Client::Client() {
    ZMQSocketConfig config = {
        ZMQ_REQ,
        &(MessageFactory::getInstance())
    };
    local_socket = new ZMQSocket(config);
    assert(local_socket != nullptr);
}

Client::~Client() {
    this->leaveData();
    this->disconnect();

    assert(local_socket != nullptr);
    delete local_socket;
    local_socket = nullptr;
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    if(this->isConnected()) { return false; }
    local_socket->connect(ip, port);

    Message* m = msgFactory.newMessage(MessageFactory::MSG_CONNECTION_REQUEST);
    assert(m != nullptr);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CONNECTION_SUCCESS) {
        msgFactory.freeMessage(m);
        this->disconnect();
        return false;
    }

    _userID = static_cast<MsgConnectionSuccess*>(m)->getUserID();
    msgFactory.freeMessage(m);

    return true;
}

bool Client::disconnect() {
    assert(local_socket != nullptr);

    if(this->isDataLoaded()) {
        this->leaveData();
    }

    if(!this->isConnected()) {
        return false;
    }

    Message* m = msgFactory.newMessage(MessageFactory::MSG_DISCONNECT_REQUEST);
    static_cast<MsgDisconnectRequest*>(m)->setUserID(_userID);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_DISCONNECT_SUCCESS) {
        msgFactory.freeMessage(m);
        return false;
    }

    _userID = -1;
    msgFactory.freeMessage(m);

    local_socket->disconnect();

    return true;
}

bool Client::createData(CollabData* data) {
    assert(data != nullptr);
    if(!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    Message* m;
    m = msgFactory.newMessage(MessageFactory::MSG_CREA_DATA_REQUEST);
    static_cast<MsgCreaDataRequest*>(m)->setUserID(_userID);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CREA_DATA_SUCCESS) {
        msgFactory.freeMessage(m);
        return false;
    }

    _data = data;
    _dataID = static_cast<MsgCreaDataSuccess*>(m)->getDataID();
    msgFactory.freeMessage(m);

    assert(_data != nullptr);
    assert(_dataID != -1);

    data->setOperationBroadcaster(*this);

    return true;
}

bool Client::joinData(CollabData* data, int dataID) {
    assert(data != nullptr);
    assert(dataID > -1);
    if(!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    Message* m = msgFactory.newMessage(MessageFactory::MSG_JOIN_DATA_REQUEST);
    static_cast<MsgJoinDataRequest*>(m)->setUserID(_userID);
    static_cast<MsgJoinDataRequest*>(m)->setDataID(dataID);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_JOIN_DATA_SUCCESS) {
        msgFactory.freeMessage(m);
        return false;
    }

    msgFactory.freeMessage(m);
    _dataID = dataID;
    _data = data;

    data->setOperationBroadcaster(*this);

    return true;
}

bool Client::leaveData() {
    if(!this->isConnected() || !this->isDataLoaded()) {
        return false;
    }

    Message* m = msgFactory.newMessage(MessageFactory::MSG_LEAVE_DATA_REQUEST);
    static_cast<MsgLeaveDataRequest*>(m)->setUserID(_userID);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_LEAVE_DATA_SUCCESS) {
        msgFactory.freeMessage(m);
        return false;
    }

    _dataID = -1;
    _data->removeOperationBroadcaster();
    _data = nullptr;
    msgFactory.freeMessage(m);

    return true;
}

void Client::onOperation(const Operation& op) {
    if(!this->isConnected() || !this->isDataLoaded()) {
        assert(false); // Should not append
        return;
    }

    Message* m = msgFactory.newMessage(MessageFactory::MSG_ROOM_OPERATION);
    static_cast<MsgRoomOperation*>(m)->setRoomID(_dataID);
    static_cast<MsgRoomOperation*>(m)->setUserID(_userID);
    // TODO Not working yet, to finish
    //static_cast<MsgRoomOperation*>(m)->setOperation(op);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_EMPTY) {
        msgFactory.freeMessage(m);
        assert(false);
        return;
    }
    msgFactory.freeMessage(m);
}


} // End namespace


