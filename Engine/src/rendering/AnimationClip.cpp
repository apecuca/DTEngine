#include <DTEngine/AnimationClip.hpp>

#include "system/SystemRegistry.hpp"
#include "system/RenderingSystem.hpp"

#include <algorithm>

using namespace DTEngine;

AnimationClip::AnimationClip(bool _loop) :
    loop(_loop)
{
    //
}

void AnimationClip::InsertFrame(int sprite, int duration)
{
    AnimationFrame newFrame(sprite, duration);
    InsertFrame(newFrame);
}

void AnimationClip::InsertFrame(AnimationFrame& frame)
{
    frames.emplace_back(frame);

    totalDuration += frame.duration;
}

const AnimationFrame& AnimationClip::GetFrame(int frame)
{
    int accumulated = 0;

    for (int i = 0; i < frames.size(); i++)
    {
        accumulated += frames[i].duration;

        if (frame < accumulated)
            return frames[i];
    }

    return frames.back();
}

int AnimationClip::GetDuration() const
{
    return totalDuration;
}

float AnimationClip::GetDurationInSeconds() const
{
    float frameRate = (float)SystemRegistry::GetSystem<RenderingSystem>()->GetAnimationFramerate();
    return ((float)totalDuration / frameRate);
}