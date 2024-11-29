#pragma once
class AbilityMgr;
class Player;
class AniSkeleton;
class MonsterPoolManager;
class MonsterSpawner;

class SceneDev3 : public Scene
{
private:
	SpriteGo* sprite;
	Player* player;
	AniSkeleton* skeleton;
	AbilityMgr* abilMgr;
	MonsterPoolManager* MPMgr;
	MonsterSpawner* monsterSpawn;
	json j;

	sf::FloatRect mapBound = { 0, 0, 1920, 1080 };
public:

	SceneDev3();
	virtual ~SceneDev3() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);

	virtual void Draw(sf::RenderWindow& window);



};

