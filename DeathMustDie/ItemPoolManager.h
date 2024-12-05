#pragma once
#include "GameObject.h"
#include "ItemPool.h"

class ItemPoolManager : public GameObject
{
private:
	std::unordered_map<std::string, ItemPool*> poolContainer;
	std::unordered_map<std::string, std::list<Item*>> items;

public:
	ItemPoolManager(const std::string& name = "");
	~ItemPoolManager() = default;
	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void CreatePool(ItemTypes type, json j, std::string name);

	std::vector<Item*> GetAllActiveItems();

	std::unordered_map<std::string, std::list<Item*>>& GetItemList() { return items; }
	int GetItemCount();
	Item* GetItem(std::string name);
};

