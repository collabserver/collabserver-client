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
        int         _dataTypeID         = -1;
        int         _nbCollaborators    = -1;
        int         _userID             = -1;

    public:
        Client();
        ~Client();

    public:

        /**
         * Try to open connection with the remote server.
         * Connection tentative may be timed out if timeout is set.
         * (Infinite timeout if value equal or inferior to 0)
         *
         * \bug
         * timeout not implemented yet
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
        bool isConnected() const { return _userID != -1; }

        /**
         * Creates new collaborative data on server and join it.
         * Data is volatile on server and won't be saved on a database.
         * Do nothing if another data is already loaded (And returns false).
         *
         * Current dataID is set with the ID server gave to this collab data.
         * You may share this ID with other in order to join the collaboration.
         *
         * This methods wait and block until server answers.
         *
         * \param dataTypeID Type of data to create (See server registered data)
         * \return True if successfully created, otherwise, return false.
         */
        bool createDataVolatile(int dataTypeID);

        /**
         * Join a collab data already started on server side.
         * Data ID is attributed by the server. You may get it from its owner.
         *
         * \param dataID Unique ID of the data on server.
         * \return True if successfully joined, otherwise, return false.
         */
        bool joinData(int dataID);

        /**
         * Leave the current data collaboration.
         * Does nothing if no data already loaded.
         *
         * \return True if successfully left, otherwise, return false.
         */
        bool leaveData();

        /**
         * Check whether a CollabServer data has been loaded.
         * If no data loaded, this means no collaboration is ongoing.
         *
         * \return True if data loaded, otherwise, return false.
         */
        bool isDataLoaded() const { return _data != nullptr; }


    // ---------------------------------------------------------------------
    // Getters / Setters
    // ---------------------------------------------------------------------

    public:
        int getNbCollaborators() const { return _nbCollaborators; }
        int getDataID() const { return _dataID; }
        int getDataTypeID() const { return _dataTypeID; }
        CollabData* getCollabData() { return _data; }
};


} // End namespace


