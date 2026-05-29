#include <DTEngine/Animator.hpp>

#include <DTEngine/AnimationClip.hpp>
#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/RenderingSystem.hpp"
#include "system/TimeSystem.hpp"

#include <iostream>
#include <algorithm>

using namespace DTEngine;

Animator::~Animator()
{
    if (!spr) {
        auto c = gameObject.GetComponent<SpriteRenderer>();
        if (!c)
            return;
        
        spr = c;
    }

    spr->animationSpriteId = -1;
}

Animator::Animator(GameObject& _gameObject) :
    Component(_gameObject)
{
    //
}

void Animator::Update()
{
    if (currentState != AnimatorState::PLAYING)
        return;

    if (!spr && !Play(currentClip))
        return;

    AnimationClip& clip = clips.at(currentClip);
    int clipDuration = clip.GetDuration();
    if (clipDuration == 0)
        return;

    if (speed >= 0.0f) {
        if (currentFrame >= clipDuration) {
            if (!clip.loop)
                return;

            timer = 0.0f;
        }
    } else {
        if (timer < 0.0f) {
            if (!clip.loop)
                return;

            timer = clip.GetDurationInSeconds();
        }
    }

    currentFrame = SystemRegistry::GetSystem<RenderingSystem>()->GetFramesInTimeInterval(timer);
    if (currentFrame > clipDuration)
        currentFrame = clipDuration;
    spr->SetAnimationSprite(clip.GetFrame(currentFrame).sprite);

    timer += SystemRegistry::GetSystem<TimeSystem>()->GetDeltaTime() * speed;
}

int Animator::AddClip(AnimationClip& clip)
{
    clips.emplace_back(clip);
    return clips.size() - 1;
}

bool Animator::Play(int clipIndex)
{
    if (clipIndex < 0 || clipIndex > clips.size() - 1)
        return false;

    if (!spr) {
        auto c = gameObject.GetComponent<SpriteRenderer>();
        if (!c)
            return false;

        spr = c;
    }

    if (clipIndex != currentClip) {
        Stop();
        currentClip = clipIndex;
        if (speed < 0.0f)
            timer = clips.at(clipIndex).GetDurationInSeconds();
    }

    Play();

    return true;
}

void Animator::Play()
{
    if (currentClip == -1)
        return;

    currentState = AnimatorState::PLAYING;
}

void Animator::Pause()
{
    if (currentState == AnimatorState::PLAYING)
        currentState = AnimatorState::PAUSED;

}

void Animator::Stop()
{
    if (!spr) {
        auto c = gameObject.GetComponent<SpriteRenderer>();
        if (!c)
            return;

        spr = c;
    }

    spr->animationSpriteId = -1;
    currentState = AnimatorState::STOPPED;
    currentClip = -1;
    timer = 0.0f;
    currentFrame = 0;
}