#pragma once
#include "AttackEntityPoolMgr.h"

class Player;
class CalculatorMgr;

class Ability : public GameObject
{
protected:
	AbilityGrade grade;
	AbilityType type;

	json info;
	CalculatorMgr* calc;
	AttackEntityPoolMgr* entityPool;

	std::string userName;
	GameObject* user;

	float level = 1;
	float timer = 0;
	float elapsedTimer = 0;
	float interval = 0;
	float duration = 0;
	int projectiles = 1;
	bool isActive = false;

	Player* player;

	std::function<AttackEntity* ()> instantiateFunc;
	std::function<void(AttackEntity*)> changeInfoFunc;
	std::function<void(AttackEntity*)> spawnFunc;

	std::vector<std::function<void(json&)>> activeHandlers;
public:
	Ability(const json& info, AttackEntityPoolMgr* pool, const std::string& user, const std::string& name = "");
	~Ability() = default;

	void Reset()override;
	void Update(float dt)override;

	void SetSkillInfo();
	void SetFunc();
	void CreateEntityPool();
	void SetInstantiateFunc();
	void SetChangeInfoFunc();
	void SetSpawnFunc();
	void UseAbility();

	void ChangeInfo(const json& j);
	void SetLevel(int level);

	AbilityGrade GetGrade() const { return this->grade; }
	void SetGrade(const AbilityGrade& grade) { this->grade = grade; }
	AbilityType GetType() const { return type; }
	int GetLevel() const { return level; }
	json GetInfo() const { return info; }
};
