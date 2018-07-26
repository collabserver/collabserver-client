#include "collabclient/Client.h"

#include <cassert>

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/messaging/Message.h"
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
    // TODO DEBUG for now, simply send debug msg
    std::unique_ptr<Message> m;
    m = config.factory->newMessage(MessageFactory::MSG_DEBUG);
    _socket->sendMessage(*m);
    return true;
}

bool Client::disconnect() {
    assert(_socket != nullptr);
    if(_socket != nullptr) {
        _socket->disconnect();
        return true;
    }
    return false;
}

bool Client::isConnected() {
    return _socket != nullptr;
}


} // End namespace


