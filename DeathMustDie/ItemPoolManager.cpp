#include "stdafx.h"
#include "ItemPoolManager.h"

ItemPoolManager::ItemPoolManager(const std::string& name)
    :GameObject(name)
{
}

void ItemPoolManager::Init()
{

}

void ItemPoolManager::Release()
{
}

void ItemPoolManager::Reset()
{
    CreatePool(ItemTypes::Gem, ITEM_TABLE->Get("Gem"), "Gem");
}

void ItemPoolManager::Update(float dt)
{
	for (auto& pair : items)
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

void ItemPoolManager::FixedUpdate(float dt)
{
	for (auto& pair : items)
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

void ItemPoolManager::Draw(sf::RenderWindow& window)
{
	for (auto& pair : items)
	{
		for (auto& entity : pair.second)
		{
			entity->Draw(window);
		}
	}
}

void ItemPoolManager::CreatePool(ItemTypes type, json j, std::string name)
{
	ItemPool* obj = new ItemPool(type, j);

	poolContainer.insert({ name, obj });
}

std::vector<Item*> ItemPoolManager::GetAllActiveItems()
{
	std::vector<Item*> activeItems;
	for (auto& pair : items)
	{
		for (auto& item : pair.second)
		{
			if (item->IsActive())
			{
				activeItems.push_back(item);
			}
		}
	}
	return activeItems;
}

int ItemPoolManager::GetItemCount()
{
	int count = 0;
	for (auto& pair : items)
	{
		for (auto& list : pair.second)
		{
			count++;
		}
	}

	return count;
}

Item* ItemPoolManager::GetItem(std::string name)
{
	ItemPool* obj = poolContainer.find(name)->second;

	Item* item = obj->Take();

	auto it = items.find(name);
	if (it == items.end())
	{
		std::list<Item*> list = { item };
		items.insert({ name, list });
	}
	else
	{
		it->second.push_back(item);
	}

	return item;
}
