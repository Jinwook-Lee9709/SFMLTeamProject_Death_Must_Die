#pragma once
#include "GameObject.h"
#include "ItemPoolManager.h"
#include "MonsterPoolManager.h"

class Monster;

class ItemSpawner : public GameObject
{
protected:
    ItemPoolManager* poolManager;

public:
    ItemSpawner(ItemPoolManager* manager);
    ~ItemSpawner() = default;

    void SpawnItemTrigger(const GameObject& go);
    void SpawnItem(const std::string& itemName, const GameObject& monster);
    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};

