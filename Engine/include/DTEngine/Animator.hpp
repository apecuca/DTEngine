#ifndef DTENGINE_ANIMATOR_H
#define DTENGINE_ANIMATOR_H

#include <DTEngine/Component.hpp>

#include <DTEngine/AnimationClip.hpp>
#include <DTEngine/EntityHandle.hpp>
#include <DTEngine/SpriteRenderer.hpp>

#include <vector>

namespace DTEngine
{

class AnimationClip;

enum AnimatorState { STOPPED, PLAYING, PAUSED };

class Animator : public Component
{
public:
	virtual ~Animator();
	Animator(GameObject& _gameObject);

public:
	// Plays a clip at the index of the saved clips
	bool Play(int clipIndex);
	// Plays the current clip
	void Play();
	// Pauses the current clip
	void Pause();

	// Stop all animations and unassignes the current clip
	void Stop();

	// Adds a clip to the Animator and returns the index of the new clip
	int AddClip(AnimationClip& clip);

private:
	void Update() override;

public:
	float speed = 1.0f;

private:
	std::vector<AnimationClip> clips;

	int currentClip = -1;
	AnimatorState currentState = AnimatorState::STOPPED;
	float timer = 0.0f;
	int currentFrame = 0;

	EntityHandle<SpriteRenderer> spr;
};

}


#endif