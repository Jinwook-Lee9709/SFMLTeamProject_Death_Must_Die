#pragma once
#include "Scene.h"


class SceneDev1 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;

public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

