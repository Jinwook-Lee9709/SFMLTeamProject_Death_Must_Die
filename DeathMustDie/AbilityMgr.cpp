#include "stdafx.h"
#include "Ability.h"
#include "AbilityMgr.h"
#include "AttackEntityPoolMgr.h"
#include "EventHandler.h"

AbilityMgr::AbilityMgr(const std::string& name)
	:GameObject(name)
{
}

void AbilityMgr::Reset()
{
	entityPool = (AttackEntityPoolMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AttackEntityPoolMgr");
	std::function<void()> func1 = std::bind(&AbilityMgr::UpdateAttack, this);
	std::function<void()> func2 = std::bind(&AbilityMgr::UpdateDash, this);
	EVENT_HANDLER.AddEvent("OnAttack", func1);
	EVENT_HANDLER.AddEvent("OnDash", func2);
}

void AbilityMgr::AddAbility(const std::string& skillId)
{
	json j = SKILL_TABLE->Get(skillId);
	Ability* abil = new Ability(j, entityPool, skillId);
	abil->Reset();
	switch ((AbilityTriggerType)j["triggerType"].get<int>())
	{
		case AbilityTriggerType::Attack:
		{
			AttackCounter counter;
			counter.maxCount = j["attackCounter"]["maxCount"].get<int>();
			counter.probability = j["attackCounter"]["probability"].get<int>();
			attack.push_back({ counter, abil });
			break;
		}
		case AbilityTriggerType::Dash:
		{
			dash.push_back(abil);
			break;
		}
		case AbilityTriggerType::AutoCast:
		{
			CoolTime time;
			time.elapsedTime = 0;
			time.coolTime = j["coolTime"];
			autoCast.push_back({ time, abil });
			break;
		}
	}
}

void AbilityMgr::Release()
{
	EVENT_HANDLER.DeleteEvenet("OnAttack");
	EVENT_HANDLER.DeleteEvenet("OnDash");
}

void AbilityMgr::Update(float dt)
{
	UpdateAll(dt);
	UpdateAutoCast(dt);
}

void AbilityMgr::UpdateAttack()
{
	for (auto& abil : attack)
	{
		if (abil.first.maxCount == 1)
		{
			if (Utils::RollTheDice(abil.first.probability))
			{
				abil.second->UseAbility();
			}
		}
		else
		{
			abil.first.currentCount++;
			if (abil.first.currentCount >= abil.first.maxCount)
			{
				abil.first.currentCount = 0;
				if (Utils::RollTheDice(abil.first.probability))
				{
					abil.second->UseAbility();
				}
			}
		}
	}
}

void AbilityMgr::UpdateDash()
{
	for (auto& abil : dash)
	{
		abil->UseAbility();
	}
}

void AbilityMgr::UpdateAutoCast(float dt)
{
	for (auto& abil: autoCast)
	{
		abil.first.elapsedTime += dt;
		if (abil.first.coolTime < abil.first.elapsedTime)
		{
			abil.first.elapsedTime = 0;
			abil.second->UseAbility();
		}
	}
}

void AbilityMgr::UpdateAll(float dt)
{
	for (auto& abil : attack)
	{
		abil.second->Update(dt);
	}
	for (auto& abil : dash)
	{
		abil->Update(dt);
	}
	for (auto& abil : autoCast)
	{
		abil.second->Update(dt);
	}
	for (auto& abil : earn)
	{
		abil->Update(dt);
	}
}
