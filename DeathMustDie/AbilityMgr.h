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

	struct Passive
	{
		IncreaseType type;
		float amount;
		int level;
		AbilityGrade grade;
	};

private:
	Ability* basicAttack;
	std::vector<std::pair<AttackCounter, Ability*>> attack;
	std::vector<Ability*> dash;
	std::vector<std::pair<CoolTime, Ability*>> autoCast;
	std::vector<Ability*> earn;
	std::unordered_map<std::string, Passive> passive;

	std::vector<Ability*> abilityList;
	//RemainAbilityList
	std::list<std::string> remainAbility;
	//Reference
	AttackEntityPoolMgr* entityPool;
public:
	AbilityMgr(const std::string& name = "AbilityMgr");
	~AbilityMgr() = default;

	int GetRemainAbilityCount() const;
	int GetRemainRegularAbilityCount() const;
	int GetRemainLegendaryAbilityCount() const;
	int GetNotMaxLvlAbilCount() const;
	int GetNotMaxGradeAbilCount() const;
	std::string GetRandomRemainAbility(bool isLegendary);
	Ability GetRandomEquipedAbility();
	Ability GetRdNotMaxLvlAbil();
	Ability GetRdNotMaxGradeAbil();

	void Reset() override;
	void AddAbility(const std::string& skillId, const std::string& user = "Player");
	void ChangeAbility(const json& info, const UpgradeType& type);
	void Release() override;
	void Update(float dt) override;
	void UpdateBasicAttack();
	void UpdateAttack();
	void UpdateDash();
	void UpdateAutoCast(float dt);
	void UpdateAll(float dt);

	void ApplyPassive(const std::string& name, IncreaseType type, float amount);


	Ability* FindAbilityByName(const std::string& name);
private:

};

#define MAX_LEVEL 30


