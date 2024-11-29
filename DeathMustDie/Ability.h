#pragma once

#include "AttackEntityPoolMgr.h"

class Ability : public GameObject
{
protected:
	AbilityGrade grade;
	AbilityType type;

	json info;
	AttackEntityPoolMgr* entityPool;

	float timer = 0;
	float elapsedTimer = 0;
	float interval = 0;
	float duration = 0;
	int projectiles = 1;
	bool isActive = false;

	std::function<void()> activateFunc;
public:
	Ability(const json& info, AttackEntityPoolMgr* pool,const std::string& name = "");
	~Ability() = default;

	void Update(float dt)override;

	void SetSkillInfo();
	void SetActivateFunc();
	void UseAbility();

	AbilityGrade GetGrade() const { return this->grade; }
	void SetGrade(const AbilityGrade& grade) { this->grade = grade; }
	AbilityType GetType() const { return type; }
};
