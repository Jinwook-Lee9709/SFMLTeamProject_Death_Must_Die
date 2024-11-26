#include "stdafx.h"
#include "Animator.h"

void Animator::Update(float dt)
{
	elapsedTime += dt;
	if (!isPlay) {
		return;
	}
	if (duration > elapsedTime) {
		return;
	}
	currentframe++;
	elapsedTime = 0;
	switch (clip->loopType) {
		case LoopType::Loop:
		{
			if (currentframe == clip->frames.size())
				currentframe = 0;
			return;
			break;
		}
		case LoopType::Single:
		{
			currentframe = -1;
			isPlay = false;
			break;
		}
	}
	target->setTextureRect(clip->frames[currentframe].texCoord);



}

void Animator::Play(AnimationClip* clip)
{
	this->clip = clip;
	isPlay = true;
	currentframe = 0;
	elapsedTime = 0;


	duration = 1.f / clip->fps;

	target->setTexture(TEXTURE_MGR.Get(clip->frames[0].texId));
	target->setTextureRect(clip->frames[0].texCoord);

}

void Animator::Stop()
{
	isPlay = false;
}
