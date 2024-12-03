#pragma once
#include "GameObject.h"

class AbilityMgr;
class UISkillSelect;


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
	UISkillSelect* skillSelectUi;
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

	void SelectSkill();
};
