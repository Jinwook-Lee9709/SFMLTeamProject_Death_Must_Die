#include "stdafx.h"
#include "FallAttack.h"

FallAttack::FallAttack(const std::string& name)
	: AttackEntity(name)
{
	fallAnimator.SetTarget(&fallSprite);
	impactAnimator.SetTarget(&impactSprite);
}

void FallAttack::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void FallAttack::SetRotation(float angle)
{
	rotation = angle;
}

void FallAttack::SetScale(const sf::Vector2f& s)
{
	scale = s;
	fallSprite.setScale(scale * info.fallAnimSize);
	impactSprite.setScale(scale);
}

void FallAttack::Release()
{
}



void FallAttack::Update(float dt)
{
	if (!isImpacted)
	{
		sf::Vector2f fallPos = fallSprite.getPosition();
		fallPos.y += info.speed * dt;
		if (fallPos.y > position.y)
		{
			isImpacted = true;
			fallPos.y = position.y;
			StartImpactAnim();
		}
		else
		{
			fallSprite.setPosition(fallPos);
		}
	}
	impactAnimator.Update(dt);
	fallAnimator.Update(dt);
	if (!impactAnimator.IsPlay() && !fallAnimator.IsPlay())
	{
		active = false;
	}
}

void FallAttack::FixedUpdate(float dt)
{
	if (isImpacted)
	{
		auto obj = SCENE_MGR.GetCurrentScene()->FindGo("Rect");
		if (obj != nullptr)
		{
			sf::FloatRect rectSize = obj->GetGlobalBounds();
			sf::Vector2f ellipseRadius = { info.ellipseWidth, info.ellipseHeight };
			if (Utils::CheckCollision(position, ellipseRadius, rectSize))
			{
				std::cout << "Hit!" << std::endl;
			}
		}
	}
	
}

void FallAttack::Draw(sf::RenderWindow& window)
{
	window.draw(fallSprite);
	window.draw(impactSprite);
}


void FallAttack::SetInfo(const json& j)
{
	info = j;
}

void FallAttack::Play()
{
	active = true;
	SetScale(scale);
	fallAnimator.Play(info.fallAnimId);
	sf::Vector2f fallPos = position;
	if (info.impactFrame == 0)
	{
		StartImpactAnim();
	}
	else
	{
		fallPos.y -= info.speed * info.impactFrame / 10;
		isImpacted = false;
	}
	fallSprite.setPosition(fallPos);
	Utils::SetOrigin(fallSprite, Origins::BC);
	 
}

void FallAttack::StartImpactAnim()
{
	impactAnimator.Play(info.impactAnimId);
	impactSprite.setPosition(position);
	Utils::SetOrigin(impactSprite, Origins::MC);
	isImpacted = true;
	
}
