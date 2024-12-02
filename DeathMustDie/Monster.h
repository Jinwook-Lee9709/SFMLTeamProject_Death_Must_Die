#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:
	float hp = 100.f;
	float tikDamage = 10.f;
	float debuffTimer = 0.f;
	float debuffInterval = 1.f;
	float debuffCount = 0.f;
	float maxDebuff = 6.f;

	bool isDebuff = false;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	virtual void SetInfo(const json& j) {}
	virtual void OnHit(float damage) {}
	virtual void OnDebuffed(DebuffType type) { }
	void Draw(sf::RenderWindow& window) override;

	void OnDeath();
	virtual void OnDebuff(float dt) {}
};

#define DISTANCE_TO_PLAYER (60.f)
