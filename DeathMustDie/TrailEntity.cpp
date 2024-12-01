#include "stdafx.h"
#include "TrailEntity.h"

TrailEntity::TrailEntity(const std::string& name)
	:AttackEntity(name)
{
}

void TrailEntity::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	hitbox.rect.setPosition(position);
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
	if (!active)
		return;

	effector.Update(dt);
	timer += dt;
	if (timer > info.duration && !isEnd)
	{
		effector.AddAnimation(info.AnimIdEnd);
		isEnd = true;
	}
	if (!effector.IsPlay() && isEnd == true)
	{
		active = false;
		isEnd = false;
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
	std::vector<Monster*> monsterBuf;
	auto& container = monsters->GetMonsterList();
	for (auto pair : container)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			if (excludedTargets.find((*it)) != excludedTargets.end())
			{
				it++;
				continue;
			}
			sf::FloatRect rect = (*it)->GetHitBox().rect.getGlobalBounds();
			if (hitbox.rect.getGlobalBounds().intersects(rect))
			{
				std::cout << "Hit!" << std::endl;
				(*it)->OnHit(info.damage);
				excludedTargets.insert({ (*it), 0 });
				monsterBuf.push_back(*it);
			}
			it++;
		}
	}
	sideEffect->TriggerEffect(monsterBuf);
}

void TrailEntity::Draw(sf::RenderWindow& window)
{
	effector.Draw(window);
}

void TrailEntity::SetInfo(const json& j)
{
	info = j;
	if (j.contains("SideEffect"))
	{
		SetSideEffect(j["SideEffect"]);
	}

	hitbox.rect.setSize({ info.width, info.height });
	Utils::SetOrigin(hitbox.rect, Origins::BC);
}

void TrailEntity::ChangeInfo(const json& j)
{
	json originalJson = info;
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (originalJson.contains(it.key()))
		{
			originalJson[it.key()] = it.value();
		}
	}
	info = originalJson;
}

void TrailEntity::Activate()
{
	active = true;
	isEnd = false;
	timer = 0;
	effector.AddAnimation(info.AnimIdStart);
	effector.AddAnimation(info.AnimIdLoop);
	SetScale(scale);
	effector.SetOrigin(Origins::BC);
}
