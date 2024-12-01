#pragma once
#include "Scene.h"

class Player;
class TileMap2;

class SceneDev1 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;

	Player* player;
	std::vector<std::vector<TileMap2*>> tiles;
	sf::Vector2i tilesCount = { 5, 5 };
public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

