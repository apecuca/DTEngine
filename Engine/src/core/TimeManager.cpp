#include <DTEngine/TimeManager.hpp>

#include "system/SystemRegistry.hpp"
#include "system/TimeSystem.hpp"

using namespace DTEngine;

float TimeManager::GetDeltaTime()
{
    return SystemRegistry::GetSystem<TimeSystem>()->GetDeltaTime();
}

void TimeManager::SetFixedTimeStep(double value)
{
    SystemRegistry::GetSystem<TimeSystem>()->SetFixedTimeStep(value);
}

double TimeManager::GetFixedTimeStep()
{
    return SystemRegistry::GetSystem<TimeSystem>()->GetFixedTimeStep();
}