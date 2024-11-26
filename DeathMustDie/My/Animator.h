#pragma once
#include "AnimationClip.h"
class Animator
{
protected:
	AnimationClip* clip;
	sf::Sprite* target;
	
	int currentframe;

	float duration;
	float elapsedTime;

	bool isPlay;
public:
	void Update(float dt);
	void Play(AnimationClip* clip);
	void Stop();
	void SetTarget(sf::Sprite* target) { this->target = target; }
};

