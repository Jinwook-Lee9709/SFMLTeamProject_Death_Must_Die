#include "stdafx.h"
#include "AttackEntityPoolMgr.h"
#include "AttackEntity.h"
#include "FallAttack.h"

AttackEntityPoolMgr::AttackEntityPoolMgr(const std::string& name)
	: GameObject(name)
{
}

void AttackEntityPoolMgr::Init()
{
}

void AttackEntityPoolMgr::Release()
{
}

void AttackEntityPoolMgr::Reset()
{
}

void AttackEntityPoolMgr::Update(float dt)
{

	for (auto& pair : attackEntities)
	{
		auto it = pair.second.begin();
		while(it != pair.second.end())
		{
			if (!(*it)->IsActive())
			{
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

void AttackEntityPoolMgr::FixedUpdate(float dt)
{
	for (auto& pair : attackEntities)
	{
		auto it = pair.second.begin();
		while (it != pair.second.end())
		{
			if (!(*it)->IsActive())
			{
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


void AttackEntityPoolMgr::Draw(sf::RenderWindow& window)
{
	for (auto& pair : attackEntities)
	{
		for (auto& entity : pair.second)
		{
			entity->Draw(window);
		}
	}
}

AttackEntity* AttackEntityPoolMgr::GetEntity(const std::string& name)
{
	//Find Pool
	auto& pool = poolContainer.find(name)->second;
	AttackEntity* entity = pool->Take();
	//Check already in
	auto it = attackEntities.find(name);
	if (it == attackEntities.end())
	{
		std::list<AttackEntity*> list = { entity };
		attackEntities.insert({ name, list });
	}
	else
	{
		it->second.push_back( entity );
	}
	return entity;
}

void AttackEntityPoolMgr::CreatePool(const std::string& name, const AttackEntityType& type, const json data)
{
	AttackEntityPool* pool = new AttackEntityPool(type, data, 10);
	poolContainer.insert({ name, pool });
}
