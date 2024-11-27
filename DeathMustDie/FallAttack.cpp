#include "stdafx.h"
#include "FallAttack.h"

FallAttack::FallAttack(const std::string& name)
	: AttackEntity(name)
{
	
}

void FallAttack::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	circle.setPosition(pos);
}

void FallAttack::SetRotation(float angle)
{
	rotation = angle;
	circle.setRotation(angle);
}

void FallAttack::SetScale(const sf::Vector2f& s)
{
	scale = s;
	circle.setScale(scale);
}

void FallAttack::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(circle, preset);
	}
}

void FallAttack::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin; 
	circle.setOrigin(origin);
}

void FallAttack::Init()
{
}

void FallAttack::Release()
{
}

void FallAttack::Reset()
{
	ellipseRadius.x = 200.f;
	ellipseRadius.y = 100.f;
	circle.setRadius(1.f);
	circle.setScale(ellipseRadius);
	circle.setFillColor(sf::Color::White);
	SetOrigin(Origins::MC);
}

void FallAttack::Update(float dt)
{
	sf::Vector2i Mousepos = InputMgr::GetMousePosition();
	SetPosition(SCENE_MGR.GetCurrentScene()->ScreenToWorld(Mousepos));
}

void FallAttack::FixedUpdate(float dt)
{
	auto obj = SCENE_MGR.GetCurrentScene()->FindGo("Rect");
	if (obj != nullptr)
	{
		sf::FloatRect rectSize = obj->GetGlobalBounds();
		if (Utils::CheckCollision(position, ellipseRadius, rectSize))
		{
			circle.setFillColor(sf::Color::Red);
		}
		else
		{
			circle.setFillColor(sf::Color::White);
		}
	}
	
	AttackEntity::Update(dt);
}

void FallAttack::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
	AttackEntity::Draw(window);
}
