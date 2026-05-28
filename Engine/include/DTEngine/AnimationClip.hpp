#ifndef DTENGINE_ANIMATIONCLIP_H
#define DTENGINE_ANIMATIONCLIP_H

#include <vector>

namespace DTEngine
{

struct AnimationFrame
{
public:
	~AnimationFrame() = default;
	AnimationFrame() = default;
	AnimationFrame(int _sprite, int _duration) :
		sprite(_sprite), duration(_duration) { }
	AnimationFrame(const AnimationFrame& other) :
		sprite(other.sprite), duration(other.duration) { }

public:
	int sprite;
	int duration;
};

class AnimationClip final
{
friend class Animator;

public:
	~AnimationClip() = default;
	AnimationClip(bool _loop);

	void InsertFrame(int sprite, int duration);
	void InsertFrame(AnimationFrame& frame);

	// Returns the corresponding AnimationFrame from the given frame
	const AnimationFrame& GetFrame(int frame);

private:
	// Returns the duration of the clip in frames
	int GetDuration() const;
	// Returns the duration of the clip in seconds
	float GetDurationInSeconds() const;

public:
	bool loop = false;

private:
	std::vector<AnimationFrame> frames;

	int totalDuration = 0;
};

}

#endif