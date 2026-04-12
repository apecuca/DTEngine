#ifndef DTENGINE_TIMESYSTEM_H
#define DTENGINE_TIMESYSTEM_H

#include "core/InternalSystem.hpp"

namespace DTEngine
{

class TimeSystem : InternalSystem
{
friend class SystemRegistry;

public:
    ~TimeSystem();
    TimeSystem();

public:
    float GetDeltaTime();

    void UpdateTimeVariables();

protected:
    bool Init() override;

private:
    double lastTime;
    double deltaTime;

};

}

#endif