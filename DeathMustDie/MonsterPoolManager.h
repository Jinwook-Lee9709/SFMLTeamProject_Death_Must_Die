#pragma once
#include "GameObject.h"
#include "MonsterPool.h"

class MonsterPoolManager : public GameObject
{
private:
	std::unordered_map<std::string, MonsterPool*> poolContainer;
	std::unordered_map<std::string, std::list<Monster*>> monsters;

public:
	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void CreatePool(MonsterTypes type, json j, std::string name);
	Monster* GetMonster(std::string name);
};

