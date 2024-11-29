#include "stdafx.h"
#include "MonsterPoolManager.h"

void MonsterPoolManager::Init()
{
}

void MonsterPoolManager::Release()
{
}

void MonsterPoolManager::Reset()
{
}

void MonsterPoolManager::Update(float dt)
{
	for (auto& pair : monsters)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			if (!(*it)->IsActive())
			{
				poolContainer[pair.first]->Return(*it);
				it = pair.second.erase(it);
			}
			else
			{
				(*it)->Update(dt);
				it++;
			}
		}
	}
}

void MonsterPoolManager::FixedUpdate(float dt)
{
	for (auto& pair : monsters)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			if (!(*it)->IsActive())
			{
				poolContainer[pair.first]->Return(*it);
				it = pair.second.erase(it);
			}
			else
			{
				(*it)->FixedUpdate(dt);
				it++;
			}
		}
	}
}

void MonsterPoolManager::Draw(sf::RenderWindow& window)
{
	for (auto& pair : monsters)
	{
		for (auto& entity : pair.second)
		{
			entity->Draw(window);
		}
	}
}

void MonsterPoolManager::CreatePool(MonsterTypes type, json j, std::string name)
{
	MonsterPool* obj = new MonsterPool(type, j);

	poolContainer.insert({ name, obj });
}

Monster* MonsterPoolManager::GetMonster(std::string name)
{
	MonsterPool* obj = poolContainer.find(name)->second;

	Monster* monster = obj->Take();

	auto it = monsters.find(name);
	if (it == monsters.end())
	{
		std::list<Monster*> list = { monster };
		monsters.insert({ name, list });
	}
	else
	{
		it->second.push_back(monster);
	}

	return monster;
}
