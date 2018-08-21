#include "collabclient/Client.h"

#include <cassert>

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/messaging/Message.h"
#include "collabcommon/messaging/MessageList.h"
#include "collabcommon/network/ZMQSocket.h"

namespace collab {


static ZMQSocket* _socket = nullptr;


Client::~Client() {
    this->disconnect();
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    ZMQSocketConfig config = {
        ZMQ_REQ,
        &g_context,
        &(MessageFactory::getInstance())
    };

    if(_socket != nullptr) {
        return false;
    }
    _socket = new ZMQSocket(config);
    assert(_socket != nullptr);
    if(_socket == nullptr) {
        return false;
    }
    _socket->connect(ip, port);
    std::unique_ptr<Message> m;
    m = config.factory->newMessage(MessageFactory::MSG_CONNECTION_REQ);
    assert(m != nullptr);
    _socket->sendMessage(*m);

    m = _socket->receiveMessage();
    if(m->getType() != MessageFactory::MSG_CONNECTION_SUCCESS) {
        // this->disconnect(); // TODO Maybe to add (To check for validity)
        return false;
    }
    // TODO Set user id from message
    return true;
}

bool Client::disconnect() {
    assert(_socket != nullptr);
    // TODO Cleanup all the data (IDs etc)
    if(_socket != nullptr) {
        _socket->disconnect();
        return true;
    }
    return false;
}

bool Client::isConnected() const {
    return _socket != nullptr && _userID != -1;
}


} // End namespace


