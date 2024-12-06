#include "stdafx.h"
#include "Ability.h"
#include "AbilityMgr.h"
#include "AttackEntityPoolMgr.h"
#include "CalculatorMgr.h"
#include "EventHandler.h"
#include "Player.h"

AbilityMgr::AbilityMgr(const std::string& name)
	:GameObject(name)
{
}

int AbilityMgr::GetRemainAbilityCount() const
{
	return remainAbility.size();
}

int AbilityMgr::GetRemainRegularAbilityCount() const
{
	int count = 0;
	auto it = remainAbility.begin();
	while (it != remainAbility.end())
	{
		json info = SKILL_TABLE->Get(*it);
		if (info["abilityGrade"].get<int>() == 0)
		{
			count++;
		}
		it++;
	}
	return count;
}

int AbilityMgr::GetRemainLegendaryAbilityCount() const
{
	std::vector<std::string> buf;
	auto it = remainAbility.begin();
	while (it != remainAbility.end())
	{
		json info = SKILL_TABLE->Get(*it);
		if (info["abilityGrade"].get<int>() == 1)
		{
			buf.push_back(*it);
		}
		it++;
	}
	return buf.size();
}

int AbilityMgr::GetNotMaxLvlAbilCount() const
{
	int count = 0;
	for (auto abil : abilityList)
	{
		if (abil->GetLevel() != MAX_LEVEL && abil->GetGrade() != AbilityGrade::Legend)
		{
			count++;
		}
	}
	return count;
}

int AbilityMgr::GetNotMaxGradeAbilCount() const
{
	int count = 0;
	for (auto abil : abilityList)
	{
		if (abil->GetGrade() != AbilityGrade::Master && abil->GetGrade() != AbilityGrade::Legend)
		{
			count++;
		}
	}
	return count;
}

std::string AbilityMgr::GetRandomRemainAbility(bool isLegendary)
{
	std::vector<std::string> buf1;
	std::vector<std::string> buf2;

	auto it1 = remainAbility.begin();
	while (it1 != remainAbility.end())
	{
		json info = SKILL_TABLE->Get(*it1);
		if (info["abilityGrade"].get<int>() == 1)
		{
			buf1.push_back(*it1);
		}
		else
		{
			buf2.push_back(*it1);
		}
		it1++;
	}
	if (isLegendary)
	{
		int index = Utils::RandomRange(0, buf1.size() - 1);
		auto it = buf1.begin();
		(std::advance(it, index));
		return *it;
	}
	else
	{
		int index = Utils::RandomRange(0, buf2.size() - 1);
		auto it = buf2.begin();
		(std::advance(it, index));
		return *it;
	}



}

Ability AbilityMgr::GetRandomEquipedAbility()
{
	int index = Utils::RandomRange(0, abilityList.size() - 1);
	auto it = abilityList.begin();
	(std::advance(it, index));
	return **it;
}

Ability AbilityMgr::GetRdNotMaxLvlAbil()
{
	std::vector<Ability> buf;
	for (auto abil : abilityList)
	{
		if (abil->GetLevel() != MAX_LEVEL && abil->GetGrade() != AbilityGrade::Legend)
		{
			buf.push_back(*abil);
		}
	}
	int index = Utils::RandomRange(0, buf.size() - 1);
	auto it = buf.begin();
	(std::advance(it, index));
	return *it;
	
}

Ability AbilityMgr::GetRdNotMaxGradeAbil()
{
	std::vector<Ability> buf;
	for (auto abil : abilityList)
	{
		if (abil->GetGrade() != AbilityGrade::Master && abil->GetGrade() != AbilityGrade::Legend)
		{
			buf.push_back(*abil);
		}
	}
	int index = Utils::RandomRange(0, buf.size() - 1);
	auto it = buf.begin();
	(std::advance(it, index));
	return *it;
}

void AbilityMgr::Reset()
{
	entityPool = (AttackEntityPoolMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AttackEntityPoolMgr");
	std::function<void()> func1 = std::bind(&AbilityMgr::UpdateBasicAttack, this);
	std::function<void()> func2 = std::bind(&AbilityMgr::UpdateAttack, this);
	std::function<void()> func3 = std::bind(&AbilityMgr::UpdateDash, this);

	EVENT_HANDLER.AddEvent("OnAttack", func1);
	EVENT_HANDLER.AddEvent("OnHit", func2);
	EVENT_HANDLER.AddEvent("OnDash", func3);

	json skillList = SKILL_TABLE->GetAll();
	auto it = skillList.begin();
	while (it != skillList.end())
	{
		if (it.value()["abilityGrade"].get<int>() != -1)
		{
			remainAbility.push_back(it.key());
		}
		it++;
	}
	AddAbility("Base Attack");
}

void AbilityMgr::AddAbility(const std::string& skillId, const std::string& user)
{
	json j = SKILL_TABLE->Get(skillId);
	auto it = std::find(remainAbility.begin(), remainAbility.end(), skillId);
	remainAbility.erase(it);
	if ((AbilityType)j["abilityType"].get<int>() == AbilityType::Passive)
	{
		auto it = j["ChangeableValue"].begin();
		IncreaseType type = (IncreaseType)j["increaseType"].get<int>();
		float amount = it.value();

		passive.insert({ skillId, {type , amount, 1, AbilityGrade::Novice} });
		ApplyPassive(skillId, type, amount);
		return;
	}

	Ability* abil = new Ability(j, entityPool, user, skillId);
	if (skillId != "Base Attack")
	{
		abilityList.push_back(abil);
	}
	abil->Reset();
	switch ((AbilityTriggerType)j["triggerType"].get<int>())
	{
		case AbilityTriggerType::BasicAttack:
		{
			if (basicAttack != nullptr)
			{
				auto it = abilityList.begin();
				while (it != abilityList.end())
				{
					if ((*it) == basicAttack)
					{
						abilityList.erase(it);
						break;
					}
					it++;
				}
				delete basicAttack;
			}
			basicAttack = abil;
			Player* player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
			std::vector<int> colorCode = j["attackColor"].get<std::vector<int>>();
			sf::Color color(colorCode[0], colorCode[1], colorCode[2]);
			player->ChangeAttackColor(color);
			break;
		}
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
		case AbilityTriggerType::Earn:
		{
			abil->UseAbility();
			earn.push_back(abil);
			break;
		}

	}

	if (j["abilityGrade"].get<int>() == 1)
	{
		abil->SetGrade(AbilityGrade::Legend);
	}
}

void AbilityMgr::ChangeAbility(const json& info, const UpgradeType& type)
{
	if (info["abilityType"].get<AbilityType>() != AbilityType::Passive)
	{
		Ability* abil = FindAbilityByName(info["name"]);

		if (type == UpgradeType::LevelUp)
		{
			json buf;
			abil->SetLevel(info["level"].get<int>() + 1);
			auto it = info["valueText"].begin();
			while (it != info["valueText"].end())
			{
				float value = SKILL_LEVEL_TABLE->Get(info["name"].get<std::string>() + "_" + it.value()["valueName"].get<std::string>() + std::to_string(abil->GetLevel()), abil->GetGrade());
				buf[it.value()["valueName"].get<std::string>()] = value;
				it++;
				std::cout << buf;
			}
			abil->ChangeInfo(buf);


		}
		else
		{
			json buf;
			abil->SetGrade((AbilityGrade)(info["grade"].get<int>() + 1));
			auto it = info["valueText"].begin();
			while (it != info["valueText"].end())
			{
				float value = SKILL_LEVEL_TABLE->Get(info["name"].get<std::string>() + "_" + it.value()["valueName"].get<std::string>() + std::to_string(abil->GetLevel()), abil->GetGrade());
				buf[it.value()["valueName"].get<std::string>()] = value;

				it++;
			}
			abil->ChangeInfo(buf);

		}
	}
	else
	{
		if (type == UpgradeType::LevelUp)
		{
			passive[info["name"]].level++;
			auto it = info["valueText"].begin();
			while (it != info["valueText"].end())
			{
				float value = SKILL_LEVEL_TABLE->Get(info["name"].get<std::string>() + "_" + it.value()["valueName"].get<std::string>() + std::to_string(passive[info["name"]].level), passive[info["name"]].grade);
				it++;
			}
		}
		else
		{
			++passive[info["name"]].grade;
			auto it = info["valueText"].begin();
			while (it != info["valueText"].end())
			{
				float value = SKILL_LEVEL_TABLE->Get(info["name"].get<std::string>() + "_" + it.value()["valueName"].get<std::string>() + std::to_string(passive[info["name"]].level), passive[info["name"]].grade);
				it++;
			}
		}
		
	}
	

}

void AbilityMgr::Release()
{
	EVENT_HANDLER.DeleteEvent("OnAttack");
	EVENT_HANDLER.DeleteEvent("OnHit");
	EVENT_HANDLER.DeleteEvent("OnDash");
}

void AbilityMgr::Update(float dt)
{
	UpdateAutoCast(dt);
	UpdateAll(dt);
}

void AbilityMgr::UpdateBasicAttack()
{
	if (basicAttack != nullptr)
	{
		basicAttack->UseAbility();
	}
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
	if (basicAttack != nullptr)
	{
		basicAttack->Update(dt);
	}
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

void AbilityMgr::ApplyPassive(const std::string& name, IncreaseType type, float amount)
{
	switch (type)
	{
		case IncreaseType::CastDamage:
		{
			CalculatorMgr* calc = (CalculatorMgr*)SCENE_MGR.GetCurrentScene()->FindGo("CalculatorMgr");
			Effect effect(EffectType::Skill, amount, (float)-1, name);
			calc->AddEffect(ValueType::Cast, effect);
		}
	}
}

Ability* AbilityMgr::FindAbilityByName(const std::string& name)
{
	if (basicAttack->GetName() == name)
	{
		return basicAttack;
	}
	for (auto pair : attack)
	{
		if (pair.second->GetName() == name)
		{
			return pair.second;
		}
	}
	for (auto abil : dash)
	{
		if (abil->GetName() == name)
		{
			return abil;
		}
	}
	for (auto pair : autoCast)
	{
		if (pair.second->GetName() == name)
		{
			return pair.second;
		}
	}
	for (auto abil : earn)
	{
		if (abil->GetName() == name)
		{
			return abil;
		}
	}

	return nullptr;
}
