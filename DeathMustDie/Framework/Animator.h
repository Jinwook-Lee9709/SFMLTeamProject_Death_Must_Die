#pragma once
#include "AnimationClip.h"

class Animator
{
protected:
	sf::Sprite* sprite;
	AnimationClip* currentClip;

	bool isPlaying;
	bool flip;

	int currentFrame = 0;
	int totalFrame = 0;

	float frameDuration;
	float accumTime;
public:
	Animator() = default;
	~Animator() = default;

	void SetTarget(sf::Sprite* target) { sprite = target; }
	
	void Update(float dt);

	
	void Play(const std::string& clipId,bool flip = false);
	void Play(AnimationClip* clip, bool flip = false);

	void Stop();

	void SetFrame(const AnimationFrame& frame);
	void SetRect(const AnimationFrame& frame);

	bool IsFlip() { return flip; }
	bool IsLoop() { return currentClip->loopType == AnimationLoopTypes::Loop; }

	const std::string& GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return "";
		return currentClip->id;
	}
};