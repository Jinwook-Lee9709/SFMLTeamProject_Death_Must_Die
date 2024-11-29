#include "stdafx.h"
#include "Timer.h"

void Timer::StartTimer(bool loop)
{
	timer = 0;
	isPlaying = true;
	isLoop = loop;
}

void Timer::SetDefaultDuration(float defaultDuration)
{
	this->defaultDuration = defaultDuration;
	this->duration = defaultDuration;
}

void Timer::SetDuration(float duration)
{
	this->duration = duration;
}

void Timer::MutiplyDuration(float multiply)
{
	this->duration = defaultDuration * multiply;
}

bool Timer::UpdateTimer(float dt)
{
	if (isPlaying)
	{
		timer += dt;
		if (timer > duration)
		{
			if (isLoop)
			{
				timer = 0;
			}
			else
			{
				isPlaying = false;
			}
			return true;
		}
		return false;
	}
	
}
