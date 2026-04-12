#include <Engine/TimeManager.hpp>

#include "core/SystemRegistry.hpp"
#include "core/TimeSystem.hpp"

using namespace DTEngine;

float TimeManager::GetDeltaTime()
{
    return SystemRegistry::GetSystem<TimeSystem>()->GetDeltaTime();
}