#pragma once
#include "stdafx.h"
#include "Monster.h"
#include "AniSkeleton.h"
#include "AniSlime.h"
#include "AniBoss.h"

class MonsterPool
{private:
	Monster* CreateObject(MonsterTypes type)
	{
		switch (type)
		{
		case MonsterTypes::Skeleton:
			return new AniSkeleton();
			break;
		case MonsterTypes::Slime:
			return new AniSlime();
			break;
		case MonsterTypes::Boss:
			return new AniBoss();
			break;
		}
	}

private:
	std::list<Monster*> unused;
	std::list<Monster*> used;

	json j;
	MonsterTypes type;
public:
	MonsterPool(MonsterTypes type, json j, int initSize = 10)
	{
		for (int i = 0; i < initSize; ++i)
		{
			auto obj = CreateObject(type);
			obj->Init();
			if (j != nullptr)
			{
				obj->SetInfo(j);
				this->j = j;
				this->type = type;
			}

			unused.push_back(obj);
		}
	}

	~MonsterPool()
	{
		for (auto obj : unused)
		{
			SCENE_MGR.GetCurrentScene()->ExcludeGo(obj);
			delete obj;
		}
		for (auto obj : used)
		{
			SCENE_MGR.GetCurrentScene()->ExcludeGo(obj);
			delete obj;
		}
	}

	Monster* Take()
	{
		if (unused.empty())
		{
			auto obj = CreateObject(type);
			obj->Init();
			if (j != nullptr)
			{
				obj->SetInfo(j);
				this->j = j;
				this->type = type;
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

	void Return(Monster* obj)
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