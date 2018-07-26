#pragma once

#include <sstream>

namespace collab {


/**
 * TODO
 */
class DataID {
    private:
        int _id = 0;

    protected:
        DataID(int id) : _id(id) {}

    public:
        virtual bool serialize(std::stringstream& buffer) const = 0;
        virtual bool unserialize(const std::stringstream& buffer) = 0;

    public:
        int uniqueID() const;
};


} // End namespace


