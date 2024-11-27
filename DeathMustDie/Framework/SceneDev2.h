#pragma once
#include "Scene.h"

class Monster;

class SceneDev2 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;
	Monster* skeleton;
	Monster* slime;
	Animator anim;

	sf::Sprite spr;
	sf::RectangleShape player;

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

