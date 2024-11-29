#pragma once
#include "stdafx.h"
#include "AttackEntity.h"
#include "FallAttack.h"
#include "WedgeAttack.h"
#include "TrailEntity.h"
#include "BasicAttack.h"

class AttackEntityPool
{
private:
	std::list<AttackEntity*> unused;
	std::list<AttackEntity*> used;
	json j;
	AttackEntityType type;
private:
	AttackEntity* CreateAttackEntity(AttackEntityType type)
	{
		switch (type)
		{
			case AttackEntityType::Wedge:
			{
				return new WedgeAttack();
			}
			case AttackEntityType::Fall:
			{
				return new FallAttack();
			}
			case AttackEntityType::Trail:
			{
				return new TrailEntity();
			}
			case AttackEntityType::BasicAttack:
			{
				return new BasicAttack();
			}
		}
	}
public:
	AttackEntityPool(AttackEntityType type, json j = nullptr, int initSize = 10)
	{
		
		for (int i = 0; i < initSize; ++i)
		{
			auto obj = CreateAttackEntity(type);
			obj->Init();
			if (j != nullptr)
			{
				obj->SetInfo(j);
				this->j = j;
				this->type = type;
			}
			else
			{
				std::cout << "AttacEntityPool: Json is NULL!!";
			}
			unused.push_back(obj);
		}
	}

	~AttackEntityPool()
	{
		for (auto obj : unused)
		{
			delete obj;
		}
		for (auto obj : used)
		{
			delete obj;
		}
	}

	AttackEntity* Take()
	{
		if (unused.empty())
		{
			auto obj = CreateAttackEntity(type);
			obj->Init();
			if (j != nullptr)
			{
				obj->SetInfo(j);
			}
			obj->Reset();
			used.push_back(obj);
			return obj;
		}

		auto obj = unused.front();
		unused.pop_front();
		used.push_back(obj);
		obj->SetActive(true);
		obj->Reset();
		return obj;
	}

	void Return(AttackEntity* obj)
	{
		auto find = std::find(used.begin(), used.end(), obj);
		if (find == used.end())
		{
			std::cout << "Invaild Obj" << std::endl;
			return;
		}
		used.erase(find);
		obj->SetActive(false);
		unused.push_back(obj);
	}

};