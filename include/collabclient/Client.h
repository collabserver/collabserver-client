#pragma once

namespace collab {


/*
 * End user client.
 *
 * TODO Documentation
 */
class Client {
    public:
        Client() = default;
        ~Client();

    public:

        /**
         * Try to open connection with the remote server.
         * Connection tentative may be timed out if timeout is set.
         *
         * \param ip        IP of the remove server.
         * \param port      Port of the remove server.
         * \param timeout   Connection timeout in seconds.
         * \return True if successfully connected, otherwise, return false
         */
        bool connect(const char* ip, const int port, const float timeout = 0.0f);

        /**
         * Stop connection with remove server.
         *
         * \return True if successfully disconnected, otherwise, return false
         */
        bool disconnect();
};


} // End namespace


