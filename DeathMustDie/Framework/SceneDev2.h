#pragma once
#include "Scene.h"

class Monster;
class AniSkeleton;
class AniSlime;
class MonsterPoolManager;
class MonsterSpawner;

class SceneDev2 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;
	Animator anim;
	AniSkeleton* aniSkeleton;
	AniSlime* aniSlime;
	json j;
	MonsterPoolManager* MPMgr;
	MonsterSpawner* monsterSpawn;

	sf::Vector2f direction;
	sf::Vector2f rectDirection;
	float speed = 70.f;
	float rectSpeed = 300.f;

	sf::CircleShape attackRange;
	sf::FloatRect mapBound = { 0, 0, 1920, 1080 };

	bool isPlaying = false;

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnSkeleton(float dt);
};

