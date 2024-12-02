#pragma once
#include "Scene.h"

class AbilityMgr;
class MonsterPoolManager;
class Player;
class TileMap;
class MonsterSpawner;

class SceneGame : public Scene
{
private:
	SpriteGo* sprite;
	Player* player;
	
	//Managers
	AbilityMgr* abilMgr;
	MonsterPoolManager* skeletonMPMgr;
	MonsterPoolManager* slimeMPMgr;
	MonsterSpawner* skeletonSpawn;
	MonsterSpawner* slimeSpawn;

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

