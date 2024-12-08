#pragma once
#include "Scene.h"

class AbilityMgr;
class AniBoss;
class ItemPoolManager;
class ItemSpawner;
class MonsterPoolManager;
class MonsterSpawner;
class Player;
class Structure;
class TileMap;
class TopUi;

class SceneGame : public Scene
{
private:
	SpriteGo* sprite;
	Player* player;
	
	//Managers
	AbilityMgr* abilMgr;
	MonsterPoolManager* MPMgr;
	ItemPoolManager* itemMPMgr;
	MonsterSpawner* monsterSpawn;
	ItemSpawner* itemSpawn;

	sf::FloatRect mapBound = { 0, 0, 1920, 1080 };
	sf::Vector2f mapFull = {10000, 10000};
	sf::Vector2f mapGrid[20][20];

	ObjectPool<Structure> struPool;
	std::list<Structure*> struList;

	TopUi* topUi;

	TileMap* map;
protected:

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::list<Structure*> GetObjList() const { return struList; }
	void SetObjPos();

	void GameOver();
};

