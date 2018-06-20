#include "collabclient/Client.h"

#include "collabclient/ServerConnection.h"

namespace collab {


Client::~Proxy() {
    ServerProxy::getInstance().disconnect();
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    return ServerProxy::getInstance().connect(ip, port, timeout);
}

bool Client::disconnect() {
    return ServerProxy::getInstance().disconnect();
}

} // End namespace


