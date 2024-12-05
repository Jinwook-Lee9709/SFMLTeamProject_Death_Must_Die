#pragma once
#include "Item.h"
#include "Gem.h"

class ItemPool
{
private:
	Item* CreateObject(ItemTypes type)
	{
		switch (type)
		{
		case ItemTypes::Gem:
			return new Gem();
			break;
		}
	}

private:
	std::list<Item*> unused;
	std::list<Item*> used;

	json j;
	ItemTypes type;
public:
	ItemPool(ItemTypes type, json j, int initSize = 10)
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

	~ItemPool()
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

	Item* Take()
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

	void Return(Item* obj)
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

