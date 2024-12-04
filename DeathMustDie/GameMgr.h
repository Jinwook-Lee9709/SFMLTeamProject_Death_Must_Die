#pragma once
#include "GameObject.h"

class Ability;
class AbilityMgr;
class UIAbilitySelect;


class GameMgr : public GameObject
{
public:
	enum class Status
	{
		None,
		IDLE,
		SELECT_SKILL
	};
protected:

	Status beforeStatus;
	Status currentStatus;
	
	AbilityMgr* abilMgr;
	UIAbilitySelect* abilSelectUI;

	std::vector<std::pair<json, UpgradeType>> selectedSkill;
public:
	GameMgr(const std::string& name = "");
	~GameMgr() = default;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateIdle(float dt);
	void UpdateSelectSkill(float dt);
	void Draw(sf::RenderWindow& window) override;

	json MakeAbilityInfo(const std::string& name, const AbilityGrade& grade);
	json MakeAbilityInfo(const Ability& abil, const UpgradeType& type);
	void SelectAbility();
	void SelectNewAbility(json& j);
	void SelectLevelUpAbility(json& j);
	void SelectGradeUpAbility(json& j);
	
	void AbilitySelected(int num);
};

#define NOVICE_PROBABILITY 0.4
#define ADEPT_PROBABILITY 0.3
#define EXPERT_PROBABILITY 0.2
#define MASTER_PROBABILITY 0.1
#define LEGEND_PROBABILITY 0.05

#define LEVELUP_PROBABILITY 0.8
#define GRADEUP_PROBABILITY 0.8