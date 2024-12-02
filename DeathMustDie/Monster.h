#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:
	float hp = 100.f;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	virtual void SetInfo(const json& j) {}
	virtual void OnHit(float damage) {};
	virtual void OnDebuffed(DebuffType type) { }
	void Draw(sf::RenderWindow& window) override;

	void OnDeath();
};

#define DISTANCE_TO_PLAYER (60.f)
