#pragma once

#include <zmq.hpp>

#include "utils/Singleton.h"

namespace collab {


class IMessage;


/**
 * C++ network server connection.
 *
 * \author  Constantin
 * \date    Dec 2017
 */
class ServerConnection : private Singleton<ServerConnection> {

    // Singleton elements
    private:
        friend Singleton<ServerConnection>;
        ServerConnection() = default;
        ~ServerConnection() = default;
    public:
        using Singleton<ServerConnection>::getInstance;


    private:
        zmq::context_t m_context;
        zmq::socket_t* m_socketSend = nullptr;
        std::string m_ip            = "localhost";
        int m_port                  = 0;
        bool m_isConnected          = false;

    public:
        bool connect(const char* ip, const int port, const float timeout = 0.0f);
        bool disconnect();
        void sendMessage(const IMessage & msg);

    public:
        bool isConnected() const;
};


} // End namespace


