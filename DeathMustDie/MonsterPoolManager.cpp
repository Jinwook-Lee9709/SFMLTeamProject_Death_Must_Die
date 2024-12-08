#include "stdafx.h"
#include "MonsterPoolManager.h"

MonsterPoolManager::MonsterPoolManager(const std::string& name)
	:GameObject(name)
{

}

void MonsterPoolManager::Init()
{
}

void MonsterPoolManager::Release()
{
	for (auto& pair : monsters)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			poolContainer[pair.first]->Return(*it);
			SCENE_MGR.GetCurrentScene()->ExcludeGo(*it);
			it = pair.second.erase(it);
		}
	}
	for (auto& pointer : poolContainer)
	{
		delete pointer.second;
	}
	monsters.clear();
	poolContainer.clear();
}

void MonsterPoolManager::Reset()
{
	CreatePool(MonsterTypes::Skeleton, MONSTER_TABLE->Get("Skeleton"), "Skeleton");
	CreatePool(MonsterTypes::Slime, MONSTER_TABLE->Get("Slime"), "Slime");
	CreatePool(MonsterTypes::Boss, MONSTER_TABLE->Get("Boss"), "Boss");
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
				SCENE_MGR.GetCurrentScene()->ExcludeGo(*it);
				it = pair.second.erase(it);
				EVENT_HANDLER.InvokeEvent("OnMonsterDie");
				EVENT_HANDLER.InvokeEvent("OnSummonMonsterDie");
			}
			else
			{
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
				SCENE_MGR.GetCurrentScene()->ExcludeGo(*it);
				it = pair.second.erase(it);
				EVENT_HANDLER.InvokeEvent("OnMonsterDie");

				EVENT_HANDLER.InvokeEvent("OnSummonMonsterDie");
			}
			else
			{
				it++;
			}
		}
	}
}

void MonsterPoolManager::Draw(sf::RenderWindow& window)
{
	/*for (auto& pair : monsters)
	{
		for (auto& entity : pair.second)
		{
			entity->Draw(window);
		}
	}*/
}

void MonsterPoolManager::CreatePool(MonsterTypes type, json j, std::string name)
{
	MonsterPool* obj = new MonsterPool(type, j);

	poolContainer.insert({ name, obj });
}

std::vector<Monster*> MonsterPoolManager::GetAllActiveMonsters()
{
	std::vector<Monster*> activeMonsters;
	for (auto& pair : monsters)
	{
		for (auto& monster : pair.second)
		{
			if (monster->IsActive())
			{
				activeMonsters.push_back(monster);
			}
		}
	}
	return activeMonsters;
}

int MonsterPoolManager::GetMonsterCount()
{
	int count = 0;
	for (auto& pair : monsters)
	{
		for (auto& list : pair.second)
		{
			count++;
		}
	}

	return count;
}

Monster* MonsterPoolManager::GetMonster(std::string name)
{
	MonsterPool* obj = poolContainer.find(name)->second;

	Monster* monster = obj->Take();
	SCENE_MGR.GetCurrentScene()->AddGo(monster);

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
void MonsterPoolManager::CheckCollisions()
{
	auto activeMonsters = GetAllActiveMonsters();

	for (size_t i = 0; i < activeMonsters.size(); ++i) 
	{
		for (size_t j = i + 1; j < activeMonsters.size(); ++j) 
		{
			if (activeMonsters[i]->CheckCollision(*activeMonsters[j])) 
			{
				activeMonsters[i]->OnCollision(activeMonsters[j]);
				activeMonsters[j]->OnCollision(activeMonsters[i]);
			}
		}
	}
}
