#include "stdafx.h"
#include "WedgeAttack.h"

WedgeAttack::WedgeAttack(const std::string& name)
	:AttackEntity(name)
{
	animator.SetTarget(&sprite);
}

void WedgeAttack::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
}

void WedgeAttack::SetRotation(float degree)
{
	rotation = degree;
	sprite.rotate(rotation + 90.f);
}

void WedgeAttack::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale * info.AnimSize);
}

void WedgeAttack::Release()
{
}

void WedgeAttack::Update(float dt)
{
	if (active)
	{
		animator.Update(dt);
	}
	if (!animator.IsPlay())
	{
		active = false;
	}
	animator.Update(dt);
}

void WedgeAttack::FixedUpdate(float dt)
{
	auto obj = SCENE_MGR.GetCurrentScene()->FindGo("Rect");
	if (excludedTargets.find(obj) != excludedTargets.end())
		return;
	if (obj != nullptr)
	{
		sf::FloatRect rectSize = obj->GetGlobalBounds();
		if (Utils::CheckCollision(position, rotation, info.rangeDegree, info.radius, rectSize))
		{
			std::cout << "Hit!" << std::endl;
			excludedTargets.insert(obj);
		}
	}

}

void WedgeAttack::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void WedgeAttack::SetInfo(const json& j)
{
	info = j;
}

void WedgeAttack::Activate()
{
	active = true;
	animator.Play(info.AnimId);
	SetScale(scale);
	Utils::SetOrigin(sprite, Origins::BC);
}
