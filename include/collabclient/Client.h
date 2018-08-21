#pragma once

#include "collabdata/custom/CollabData.h"

namespace collab {


/*
 * \brief
 * End user client interface.
 *
 * Module to connect a remote CollabServer and work on a CollabData.
 * Only one CollabData can be active at the same time.
 */
class Client {
    private:
        CollabData* _data               = nullptr;
        int         _dataID             = -1;
        int         _dataType           = -1;
        int         _nbCollaborators    = -1;
        int         _userID             = -1;

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
        bool isConnected() const;

        /**
         * Creates new collaborative data on server and join it.
         * Data is volative on server and won't be saved on a database.
         *
         * Creates a new collaborative instance on server for a given data type.
         * The collab instance has a unique ID that you can
         * recover so that other users may join this collaborative data.
         *
         * This methods wait and block until server answer.
         *
         * \param dataType Type of data to create (See server registered data)
         * \return True if successfully created, otherwise, return false.
         */
        bool createVolatile(int dataType);

        /**
         * Check whether a CollabServer data has been loaded.
         * If no data loaded, this means no collaboration is ongoing.
         *
         * \return True if data loaded, otherwise, return false.
         */
        bool isDataLoaded() const {
            return _data != nullptr;
        }


    // ---------------------------------------------------------------------
    // Getters / Setters
    // ---------------------------------------------------------------------

    public:
        int getNbCollaborators() const { return _nbCollaborators; }
        int getDataID() const { return _dataID; }
        int getDataType() const { return _dataType; }
        CollabData* getCollabData() { return _data; }
};


} // End namespace


