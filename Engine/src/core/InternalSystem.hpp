#ifndef DTENGINE_INTERNALWORK_H
#define DTENGINE_INTERNALWORK_H

namespace DTEngine 
{

class InternalSystem
{
friend class SystemRegistry;

protected:
    ~InternalSystem() = default;
    InternalSystem() = default;

    virtual bool Init() = 0;
};

}

#endif