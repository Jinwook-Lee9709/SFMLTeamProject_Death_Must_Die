#pragma once
#include "Scene.h"

class Player;
class TileMap2;
class Structure;

class SceneDev1 : public Scene
{
protected:
	SpriteGo* sprite;
	TextGo* text;

	ObjectPool<Structure> struPool;
	std::list<Structure*> struList;

	Player* player;
public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::list<Structure*> GetObjList() const { return struList; }
	void SetObjPos();
};

