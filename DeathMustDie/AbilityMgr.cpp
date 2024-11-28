#include "stdafx.h"
#include "Ability.h"
#include "AbilityMgr.h"
#include "AttackEntityPoolMgr.h"

AbilityMgr::AbilityMgr(const std::string& name)
	:GameObject(name)
{
}

void AbilityMgr::Reset()
{
	entityPool = (AttackEntityPoolMgr*)SCENE_MGR.GetCurrentScene()->FindGo("entityPoolMgr");
}

void AbilityMgr::Update(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& abil : cast)
		{
			abil->UseAbility();
		}
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		for (auto& abil : strike)
		{
			abil->UseAbility();
		}
	}
}

void AbilityMgr::AddAbility(const std::string& skillId)
{
	json j = SKILL_TABLE->Get(skillId);
	Ability* abil = new Ability(j, entityPool, skillId);
	abil->SetSkillInfo();
	switch ((AbilityType)j["abilityType"].get<int>())
	{
		case AbilityType::Strike:
		{
			strike.push_back(abil);
			break;
		}
		case AbilityType::Cast:
		{
			cast.push_back(abil);
			break;
		}
	}
}
