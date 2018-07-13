#include "collabclient/Client.h"

#include <cassert>

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/network/Network.h"
#include "collabcommon/network/ZMQSocket.h"

namespace collab {


static ZMQSocket*   _socket = nullptr;


Client::~Client() {
    this->disconnect();
    network::shutdownNetwork();
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    network::initNetwork();

    ZMQSocketConfig config = {
        ZMQ_REQ,
        &network::g_context,
        &(MessageFactory::getInstance())
    };

    assert(_socket == nullptr);
    if(_socket != nullptr) {
        return false;
    }
    _socket = new ZMQSocket(config);
    if(_socket == nullptr) {
        return false;
    }
    return _socket->connect(ip, port);
}

bool Client::disconnect() {
    assert(_socket != nullptr);
    if(_socket != nullptr) {
        return _socket->disconnect();
    }
    return false;
}

bool Client::isConnected() {
    return _socket != nullptr;
}


} // End namespace


