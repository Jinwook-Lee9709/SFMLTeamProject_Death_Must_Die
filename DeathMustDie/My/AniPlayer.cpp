#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer::Init()
{
	std::string texId = "graphics/sprite_sheet.png";
	animator.SetTarget(&body);
	idle.fps = 10;
	idle.loopType = LoopType::Loop;
	sf::IntRect coord{ 0, 0, 120, 120 };
	for (int i = 0; i < 8; i++) {
		idle.frames.push_back(AnimationFrame(texId, coord));
		coord.left += 120;
	}
	animator.Play(&idle);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
