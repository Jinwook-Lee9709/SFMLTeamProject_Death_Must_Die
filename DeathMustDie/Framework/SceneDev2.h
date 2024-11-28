#pragma once
#include "Scene.h"

class Monster;
class AniSkeleton;
class AniSlime;

class SceneDev2 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;
	Animator anim;
	AniSkeleton* aniSkeleton;
	AniSlime* aniSlime;
	json j;

	sf::Vector2f direction;
	sf::Vector2f rectDirection;
	float speed = 70.f;
	float rectSpeed = 300.f;

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

	void SpawnSkeleton(int count);
};

