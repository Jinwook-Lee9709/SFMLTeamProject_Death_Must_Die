#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:
	float hp;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	virtual void SetInfo(const json& j) {}
	void Draw(sf::RenderWindow& window) override;
};

#define DISTANCE_TO_PLAYER (60.f)
