#pragma once

#include "collabdata/custom/CollabData.h"
#include "DataID.h"

namespace collab {


/*
 * End user client.
 *
 * TODO Documentation
 */
class Client {
    private:
        CollabData* _data;

    public:
        Client() = default;
        ~Client();

    public:

        /**
         * Try to open connection with the remote server.
         * Connection tentative may be timed out if timeout is set.
         * (Infinite timeout if value equal or inferior to 0)
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

        /**
         * Check whether client is currently connected to a CollabServer.
         *
         * \return True if connected, otherwise, return false.
         */
        bool isConnected();

        /**
         * TODO
         */
        CollabData* createVolatile(int dataType, int dataID);
};


} // End namespace


