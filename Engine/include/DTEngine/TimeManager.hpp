#ifndef DTENGINE_TIMEMANAGER_H
#define DTENGINE_TIMEMANAGER_H

//
// This class serves as a communication interface 
// with the internal time system
// 

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