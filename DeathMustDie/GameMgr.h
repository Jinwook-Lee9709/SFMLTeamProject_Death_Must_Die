#pragma once
#include "GameObject.h"

class Ability;
class AbilityMgr;
class CalculatorMgr;
class DamageText;
class Effector;
class UIAbilitySelect;
class Player;
class Timer;


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

	Effector* effector;

	Status beforeStatus;
	Status currentStatus;
	
	AbilityMgr* abilMgr;
	CalculatorMgr* calc;
	UIAbilitySelect* uiAbilSelect;

	ObjectPool<DamageText> textPool;
	std::list<DamageText*> textList;

	Player* player;

	Timer timer;
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

	void OnLevelUp();

	json MakeAbilityInfo(const std::string& name, const AbilityGrade& grade);
	json MakeAbilityInfo(const Ability& abil, const UpgradeType& type);
	void SelectAbility();
	void SelectNewAbility(json& j);
	void SelectLevelUpAbility(json& j);
	void SelectGradeUpAbility(json& j);

	void AbilitySelected(int num);
	void IncreaseEXP();

	void PopUpDamageText(const GameObject& go, float damage);
};

#define NOVICE_PROBABILITY 0.4
#define ADEPT_PROBABILITY 0.3
#define EXPERT_PROBABILITY 0.2
#define MASTER_PROBABILITY 0.1
#define LEGEND_PROBABILITY 0.05

#define LEVELUP_PROBABILITY 0.8
#define GRADEUP_PROBABILITY 0.8

#define GEM_EXP 5