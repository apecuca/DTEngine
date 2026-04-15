#ifndef DTENGINE_TIMEMANAGER_H
#define DTENGINE_TIMEMANAGER_H

namespace DTEngine
{

class TimeManager final
{

public:
    static float GetDeltaTime();

private:
    ~TimeManager() = default;
    TimeManager() = default;

};

}

#endif