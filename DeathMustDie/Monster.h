#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	virtual void SetInfo(const json& j) {}
};

