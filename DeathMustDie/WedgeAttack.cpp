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
	sprite.setRotation(rotation + 90.f);
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
		excludedTargets.clear();
		active = false;
	}
	animator.Update(dt);
}

void WedgeAttack::FixedUpdate(float dt)
{
	std::vector<Monster*> monsterBuf;
	auto& container = monsters->GetMonsterList();
	for (auto pair : container)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			if (excludedTargets.find(*it) != excludedTargets.end())
			{
				it++;
				continue;
			}
			sf::FloatRect rect= (*it)->GetHitBox().rect.getGlobalBounds();
			if (Utils::CheckCollision(position, rotation, info.rangeDegree, info.radius, rect))
			{
				(*it)->OnHit(info.damage);
				std::cout << "Hit!" << std::endl;
				excludedTargets.insert((*it));
				monsterBuf.push_back(*it);
			}
			it++;
		}
	}
	sideEffect->TriggerEffect(monsterBuf);
}

void WedgeAttack::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void WedgeAttack::SetInfo(const json& j)
{
	info = j;
	if (j.contains("SideEffect"))
	{
		SetSideEffect(j["SideEffect"]);
	}
}

void WedgeAttack::ChangeInfo(const json& j)
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

void WedgeAttack::Activate()
{
	active = true;
	animator.Play(info.AnimId);
	SetScale(scale);
	Utils::SetOrigin(sprite, Origins::BC);
}
