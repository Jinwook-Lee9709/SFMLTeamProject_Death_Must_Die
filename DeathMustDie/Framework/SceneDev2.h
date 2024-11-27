#pragma once
#include "Scene.h"

class SceneDev2 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

