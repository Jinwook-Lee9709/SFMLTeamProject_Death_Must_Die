#include "stdafx.h"
#include "GameMgr.h"
#include "AbilityMgr.h"
#include "UISkillSelect.h"

GameMgr::GameMgr(const std::string& name)
	: GameObject(name)
{
}
void GameMgr::Init()
{
}

void GameMgr::Release()
{
}

void GameMgr::Reset()
{
	abilMgr = (AbilityMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AbilityMgr");
	skillSelectUi = (UISkillSelect*)SCENE_MGR.GetCurrentScene()->FindGo("UISkillSelect");

}

void GameMgr::Update(float dt)
{
	switch (currentStatus)
	{
		case Status::IDLE:
		{
			UpdateIdle(dt);
			break;
		}
		case Status::SELECT_SKILL:
		{
			UpdateSelectSkill(dt);
			break;
		}
	}
}

void GameMgr::UpdateIdle(float dt)
{

}

void GameMgr::UpdateSelectSkill(float dt)
{
	if (beforeStatus != Status::None)
	{
		
	}
}

void GameMgr::Draw(sf::RenderWindow& window)
{
}

void GameMgr::SelectSkill()
{
	if (abilMgr->GetRemainAbilityCount() != 0)
	{
		//GetNewAbility
		if (Utils::RollTheDice(0.7f))
		{
			abilMgr->GetRandomRemainAbility();
		}
		else //Upgrade Ability, Increase Level / Upgrade Grade by 80 / 20
		{
			if (Utils::RollTheDice(0.8f)) // Increase Level 
			{

			}
			else // Upgrade Grade
			{

			}
		}
	}
}
