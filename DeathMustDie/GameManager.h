#pragma once
#include "GameObject.h"

class UISkillSelect;

class GameManager : public GameObject
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
	
	UISkillSelect* skillSelectUi;
public:
	GameManager(const std::string& name = "");
	~GameManager() = default;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateIdle(float dt);
	void UpdateSelectSkill(float dt);
	void Draw(sf::RenderWindow& window) override;
};
