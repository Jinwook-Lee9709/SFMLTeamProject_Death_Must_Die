#pragma once
#include "GameObject.h"

class Item : public GameObject
{
protected:

public:
	Item(const std::string& name = "");
	~Item() = default;

	virtual void SetInfo(const json& j) {}

	void Draw(sf::RenderWindow& window) override;
	void OnActtive();
};

