#include "collabclient/Client.h"

#include "ServerConnection.h"

namespace collab {


Client::~Client() {
    ServerConnection::getInstance().disconnect();
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    return ServerConnection::getInstance().connect(ip, port, timeout);
}

bool Client::disconnect() {
    return ServerConnection::getInstance().disconnect();
}


} // End namespace


