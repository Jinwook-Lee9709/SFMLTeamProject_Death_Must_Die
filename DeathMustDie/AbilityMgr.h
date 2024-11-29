#pragma once
class Ability;
class AttackEntityPoolMgr;

class AbilityMgr : public GameObject
{
	struct AttackCounter
	{
		int maxCount;
		int currentCount = 0;
		float probability;
	};

	struct CoolTime
	{
		float elapsedTime;
		float coolTime;
	};

private:
	std::vector<std::pair<AttackCounter, Ability*>> attack;
	std::vector<Ability*> dash;
	std::vector<std::pair<CoolTime, Ability*>> autoCast;
	std::vector<Ability*> earn;

	//Reference
	AttackEntityPoolMgr* entityPool;
public:
	AbilityMgr(const std::string& name = "");
	~AbilityMgr() = default;

	void Reset() override;
	void AddAbility(const std::string& skillId);

	void Update(float dt) override;
	void UpdateAttack(float dt);
	void UpdateAutoCast(float dt);
	void UpdateAll(float dt);

private:

};


