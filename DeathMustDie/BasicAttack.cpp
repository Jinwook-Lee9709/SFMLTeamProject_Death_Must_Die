#include "stdafx.h"
#include "BasicAttack.h"

BasicAttack::BasicAttack(const std::string& name)
	:AttackEntity()
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
	std::vector<Monster*> monsterBuf;
	auto& container = monsters->GetMonsterList();
	for (auto pair : container)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			sf::FloatRect rect = (*it)->GetHitBox().rect.getGlobalBounds();
			sf::Vector2f look = 10.f * Utils::AngleToVector(rotation);
			look.x *= 2;
			float margin = Utils::Magnitude(look);
			if (Utils::CheckCollision(position, rotation, info.rangeDegree, info.radius + margin, rect))
			{
				(*it)->OnHit(info.damage);
				std::cout << "Hit!" << std::endl;
				monsterBuf.push_back(*it);
			}
			it++;
		}
	
	}
	sideEffect->TriggerEffect(monsterBuf);
	if (!monsterBuf.empty())
	{
		EVENT_HANDLER.InvokeEvent("OnHit");
	}
	active = false;
}

void BasicAttack::Draw(sf::RenderWindow& window)
{
}

void BasicAttack::SetInfo(const json& j)
{
	info = j;
	if (j.contains("SideEffect"))
	{
		SetSideEffect(j["SideEffect"]);
	}
}

void BasicAttack::ChangeInfo(const json& j)
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

void BasicAttack::Activate()
{
	active = true;
	SetScale(scale);
}
