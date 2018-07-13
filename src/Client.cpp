#include "collabclient/Client.h"

namespace collab {


Client::~Client() {
    this->disconnect();
}

bool Client::connect(const char* ip, const int port, const float timeout) {
    // TODO call ZMQSocket::connet
    return false;
}

bool Client::disconnect() {
    // TODO call ZMQSocket::disconnect
    return false;
}


} // End namespace


