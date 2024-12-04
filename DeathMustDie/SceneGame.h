#pragma once
#include "Scene.h"

class AbilityMgr;
class MonsterPoolManager;
class ItemPoolManager;
class Player;
class TileMap;
class MonsterSpawner;
class ItemSpawner;
class AniBoss;

class SceneGame : public Scene
{
private:
	SpriteGo* sprite;
	Player* player;
	
	//Managers
	AbilityMgr* abilMgr;
	MonsterPoolManager* MPMgr;
	ItemPoolManager* itemMPMgr;
	MonsterSpawner* skeletonSpawn;
	ItemSpawner* itemSpawn;

	sf::FloatRect mapBound = { 0, 0, 1920, 1080 };

	json j;


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


};

