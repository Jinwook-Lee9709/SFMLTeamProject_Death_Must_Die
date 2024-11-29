#include "stdafx.h"
#include "BasicAttack.h"

BasicAttack::BasicAttack(const std::string& name)
	:AttackEntity(name)
{
}

void BasicAttack::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void BasicAttack::SetRotation(float degree)
{
	rotation = degree;
}

void BasicAttack::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void BasicAttack::Release()
{

}

void BasicAttack::Update(float dt)
{
}

void BasicAttack::FixedUpdate(float dt)
{
	auto obj = SCENE_MGR.GetCurrentScene()->FindGo("Rect");
	if (excludedTargets.find(obj) != excludedTargets.end())
		return;
	if (obj != nullptr)
	{
		std::cout << position.x << " " << position.y << std::endl;
		sf::FloatRect rectSize = obj->GetGlobalBounds();
		sf::Vector2f look = 10.f * Utils::AngleToVector(rotation);
		look.x *= 2;
		float margin = Utils::Magnitude(look);
		if (Utils::CheckCollision(position, rotation, info.rangeDegree, info.radius + margin, rectSize))
		{
			std::cout << "Hit!" << std::endl;
			excludedTargets.insert(obj);
		}
	}
	active = false;
}

void BasicAttack::Draw(sf::RenderWindow& window)
{
}

void BasicAttack::SetInfo(const json& j)
{
	info = j;
}

void BasicAttack::Activate()
{
	active = true;
	SetScale(scale);
}
