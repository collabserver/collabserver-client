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
        &g_context,
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
    if(this->isConnected()) {
        return false;
    }
    local_socket->connect(ip, port);

    Message* m = msgFactory.newMessage(MessageFactory::MSG_CONNECTION_REQUEST);
    assert(m != nullptr);
    local_socket->sendMessage(*m);
    msgFactory.freeMessage(m);

    m = local_socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CONNECTION_SUCCESS) {
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
        // TODO leave data from server
    }

    if(this->isConnected()) {
        // TODO leave server
    }

    local_socket->disconnect(); // TODO if zmq not connect, I'm not sure if this works
    return true;
}

bool Client::createDataVolatile(int dataTypeID) {
    if(this->isDataLoaded()) {
        return false;
    }
    // TODO Create on server
    // TODO Join collab room
    return false;
}

bool Client::joinData(int dataID) {
    // TODO Join collab Room
    return false;
}

bool Client::leaveData() {
    if(!this->isDataLoaded()) {
        return false;
    }
    // TODO Leave room
    return false;
}


} // End namespace


