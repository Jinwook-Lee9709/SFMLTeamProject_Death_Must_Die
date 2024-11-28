#pragma once

class Ability;
class AttackEntityPoolMgr;

class AbilityMgr : public GameObject
{
private:
	std::vector<Ability*> attack;
	std::vector<Ability*> dash;
	std::vector<Ability*> strike;
	std::vector<Ability*> cast;

	//Reference
	AttackEntityPoolMgr* entityPool;
public:
	AbilityMgr(const std::string& name = "");
	~AbilityMgr() = default;

	void Reset() override;
	void Update(float dt) override;
	void AddAbility(const std::string& skillId);

private:
};


