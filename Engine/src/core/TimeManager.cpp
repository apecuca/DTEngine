#include <Engine/TimeManager.hpp>

#include "system/SystemRegistry.hpp"
#include "system/TimeSystem.hpp"

using namespace DTEngine;

float TimeManager::GetDeltaTime()
{
    return SystemRegistry::GetSystem<TimeSystem>()->GetDeltaTime();
}