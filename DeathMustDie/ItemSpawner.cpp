#include "stdafx.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(ItemPoolManager* manager)
	:GameObject("ItemSpawner"), poolManager(manager)
{
}

void ItemSpawner::SpawnItemTrigger(const GameObject& monster)
{
	SpawnItem("Gem", monster);
}

void ItemSpawner::SpawnItem(const std::string& itemName, const GameObject& monster)
{
	sf::Vector2f monsterPos = monster.GetPosition();

	Item* item = poolManager->GetItem(itemName);
	if (item)
	{
		item->SetPosition(monsterPos);
		item->SetScale({ 3.f, 3.f });
	}
}

void ItemSpawner::Init()
{
	
}

void ItemSpawner::Reset()
{
	std::function<void(const GameObject&)> func1 = std::bind(&ItemSpawner::SpawnItemTrigger, this, std::placeholders::_1);

	EVENT_HANDLER.AddEventGo("OnMonsterDie", func1);
}

void ItemSpawner::Update(float dt)
{

}
