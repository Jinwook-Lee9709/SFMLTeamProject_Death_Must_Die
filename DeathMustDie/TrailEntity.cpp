#include "stdafx.h"
#include "TrailEntity.h"

TrailEntity::TrailEntity(const std::string& name)
	:AttackEntity(name)
{
}

void TrailEntity::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	effector.SetPosition(position);
}

void TrailEntity::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	effector.SetScale(scale);
}

void TrailEntity::Release()
{
}

void TrailEntity::Update(float dt)
{
	if (active)
	{
		effector.Update(dt);
	}
	timer += dt;
	if (timer > info.duration)
	{
		effector.AddAnimation(info.AnimIdEnd);
	}
	auto it = excludedTargets.begin();
	while (it != excludedTargets.end())
	{
		(*it).second += dt;
		if ((*it).second > info.interval)
		{
			it = excludedTargets.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void TrailEntity::FixedUpdate(float dt)
{
	auto obj = SCENE_MGR.GetCurrentScene()->FindGo("Rect");
	if (excludedTargets.find(obj) != excludedTargets.end())
		return;
	if (obj != nullptr)
	{
		sf::FloatRect rectSize = obj->GetGlobalBounds();
		std::cout << "Hit!" << std::endl;
		excludedTargets.insert({ obj, 0.f});
	}
}

void TrailEntity::Draw(sf::RenderWindow& window)
{
	effector.Draw(window);
}

void TrailEntity::SetInfo(const json& j)
{
	info = j;
}

void TrailEntity::Activate()
{
	active = true;
	timer = 0;
	effector.AddAnimation(info.AnimIdStart);
	effector.AddAnimation(info.AnimIdLoop);
	SetScale(scale);
	effector.SetOrigin(Origins::BC);
}
