#include "stdafx.h"
#include "AniMonster.h"

AniMonster::AniMonster(const std::string& name)
	: GameObject(name)
{
}

void AniMonster::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniMonster::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniMonster::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniMonster::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniMonster::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniMonster::Init()
{
	std::string texId = "resource/texture/Sheet/Skeleton_Walk_Sheet.png";
	animator.SetTarget(&body);
	idle.fps = 10;
	idle.loopType = AnimationLoopTypes::Loop;
	sf::IntRect coord{ 0, 0, 25, 46 };
	for (int i = 0; i < 7; i++) {
		idle.frames.push_back(AnimationFrame(texId, coord));
		if (i == 4)
		{
			coord.left = 0;
			coord.top += 46;
		}
		coord.left += 25;
	}
	animator.Play(&idle);
}

void AniMonster::Release()
{
}

void AniMonster::Reset()
{
}

void AniMonster::Update(float dt)
{
	animator.Update(dt);
}

void AniMonster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
