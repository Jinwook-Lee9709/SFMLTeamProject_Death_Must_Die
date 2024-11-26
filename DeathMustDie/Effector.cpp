#include "stdafx.h"
#include "Effector.h"

Effector::Effector(const std::string& name)
	: GameObject(name)
{
}

void Effector::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
}

void Effector::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
}

void Effector::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sprite.setScale(scale);
}

void Effector::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(sprite, originPreset);
	}
}

void Effector::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void Effector::Init()
{
}


void Effector::Reset()
{
	animator.SetTarget(&sprite);
}

void Effector::Update(float dt)
{
	if ((!isPlaying && !animationQueue.empty()) || (isPlaying && !animationQueue.empty() && animator.IsLoop()))
	{
		PlayAnimation(animationQueue.front());
		animationQueue.pop();
		timer = 0;
		isPlaying = true;
	}
	if (isPlaying && !animator.IsLoop())
	{
		timer += dt;
		if (timer > duration)
		{
			isPlaying = false;
		}
	}
	

	animator.Update(dt);
}

void Effector::Draw(sf::RenderWindow& window)
{
	if (isPlaying)
	{
		window.draw(sprite);
	}
	
}

void Effector::SetDuration(float duration)
{
	this->duration = duration;
}

void Effector::AddAnimation(std::string animId)
{
	animationQueue.push(animId);
}

void Effector::PlayAnimation(std::string animId)
{
	animator.Play(animId);
	SetOrigin(originPreset);
	this->active = true;
}
