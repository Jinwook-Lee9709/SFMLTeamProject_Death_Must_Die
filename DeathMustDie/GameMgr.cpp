#include "stdafx.h"
#include "GameMgr.h"
#include "Ability.h"
#include "AbilityMgr.h"
#include "CalculatorMgr.h"
#include "Player.h"
#include "UIAbilitySelect.h"


GameMgr::GameMgr(const std::string& name)
	: GameObject(name)
{
}
void GameMgr::Init()
{
}

void GameMgr::Release()
{
	EVENT_HANDLER.DeleteEvent("PanelClicked");
	EVENT_HANDLER.DeleteEvent("GemEarned");
	EVENT_HANDLER.DeleteEvent("LevelUp");
}

void GameMgr::Reset()
{
	abilMgr = (AbilityMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AbilityMgr");
	uiAbilSelect = (UIAbilitySelect*)SCENE_MGR.GetCurrentScene()->FindGo("UIAbilitySelect");
	calc = (CalculatorMgr*)SCENE_MGR.GetCurrentScene()->FindGo("CalculatorMgr");
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
	currentStatus = Status::IDLE;

	EVENT_HANDLER.AddEventInt("PanelClicked", std::bind(&GameMgr::AbilitySelected, this, std::placeholders::_1));
	EVENT_HANDLER.AddEvent("GemEarned", std::bind(&GameMgr::IncreaseEXP, this));
	EVENT_HANDLER.AddEvent("LevelUp", std::bind(&GameMgr::OnLevelUp,this));
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
	if (InputMgr::GetKeyDown(sf::Keyboard::T))
	{
		beforeStatus = Status::IDLE;
		currentStatus = Status::SELECT_SKILL;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Y))
	{
		AbilitySelected(0);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F))
	{
		uiAbilSelect->EnableUI();
		beforeStatus = Status::IDLE;
		currentStatus = Status::SELECT_SKILL;
	}
}

void GameMgr::UpdateSelectSkill(float dt)
{
	if (beforeStatus != Status::None)
	{
		SelectAbility();
		beforeStatus = Status::None;
		currentStatus = Status::IDLE;
	}
}

void GameMgr::Draw(sf::RenderWindow& window)
{
}

void GameMgr::OnLevelUp()
{
	FRAMEWORK.SetTimeScale(0);
	uiAbilSelect->EnableUI();
	beforeStatus = Status::IDLE;
	currentStatus = Status::SELECT_SKILL;
}

json GameMgr::MakeAbilityInfo(const std::string& name, const AbilityGrade& grade)
{
	json skillInfo = SKILL_TABLE->Get(name);
	json buf;
	buf["name"] = name;
	buf["abilityType"] = skillInfo["abilityType"];
	buf["level"] = 1;
	int size = skillInfo["ChangeableValue"].size();
	if (size != 0)
	{
		int i = 0;

		Stat& stat = player->GetStat();
		float min = calc->GetValue(skillInfo["abilityType"].get<AbilityType>(), stat.attack.attackDamageMin);
		float max = calc->GetValue(skillInfo["abilityType"].get<AbilityType>(), stat.attack.attackDamageMax);
		auto it = skillInfo["ChangeableValue"].begin();
		json valueText;
		while (it != skillInfo["ChangeableValue"].end())
		{
			float value;

			valueText["value" + std::to_string(i)]["valueName"] = it.key();
			if (grade != AbilityGrade::Legend)
			{
				value = SKILL_LEVEL_TABLE->Get(name + "_" + it.key() + std::to_string(buf["level"].get<int>()), grade);
			}
			else
			{
				value = it.value();
			}
			int min_value = min * value;
			int max_value = max * value;
			valueText["value" + std::to_string(i)]["value"] = std::to_string(min_value)+"-"+std::to_string(max_value);
			
			it++;
			i++;
		}
		buf["valueText"] = valueText;
		buf["valueCount"] = i;
	}
	buf["grade"] = grade;
	return buf;
}

json GameMgr::MakeAbilityInfo(const Ability& abil, const UpgradeType& type)
{
	json skillInfo = abil.GetInfo();
	json buf;
	buf["name"] = abil.GetName();
	buf["abilityType"] = abil.GetType();
	buf["level"] = abil.GetLevel();
	Stat& stat = player->GetStat();
	float min = calc->GetValue(skillInfo["abilityType"].get<AbilityType>(), stat.attack.attackDamageMin);
	float max = calc->GetValue(skillInfo["abilityType"].get<AbilityType>(), stat.attack.attackDamageMax);
	int size = skillInfo["ChangeableValue"].size();
	if (size != 0)
	{
		int i = 0;
		auto it = skillInfo["ChangeableValue"].begin();
		json valueText;
		while (it != skillInfo["ChangeableValue"].end())
		{

			valueText["value" + std::to_string(i)]["valueName"] = it.key();
			float value;
			if (type == UpgradeType::LevelUp)
			{
				value = SKILL_LEVEL_TABLE->Get(buf["name"].get<std::string>() + "_" + it.key() + std::to_string(buf["level"].get<int>() + 1), abil.GetGrade());
			}
			else
			{
				value = SKILL_LEVEL_TABLE->Get(buf["name"].get<std::string>() + "_" + it.key() + std::to_string(buf["level"].get<int>()), abil.GetGrade());
			}
			int min_value = min * value;
			int max_value = max * value;
			valueText["value" + std::to_string(i)]["value"] = std::to_string(min_value) + "-" + std::to_string(max_value);
			it++;
			i++;
		}
		buf["valueText"] = valueText;
		buf["valueCount"] = i;
	}
	buf["grade"] = abil.GetGrade();

	return buf;
}

void GameMgr::SelectAbility()
{
	selectedSkill.clear();
	std::vector<std::string> selectedList;
	bool flag = true;
	while (flag)
	{
		json abilityInfo;
		UpgradeType type = UpgradeType::Earn;
		if (abilMgr->GetRemainAbilityCount() != 0)
		{
			if (abilMgr->GetNotMaxLvlAbilCount() < 1 && abilMgr->GetNotMaxGradeAbilCount() < 1)
			{
				SelectNewAbility(abilityInfo);
			}
			else
			{
				if (Utils::RollTheDice(0.7f))
				{
					SelectNewAbility(abilityInfo);

				}
				else //Upgrade Ability, Increase Level / Upgrade Grade by 80 / 20
				{
					if (abilMgr->GetNotMaxLvlAbilCount() > 0 && abilMgr->GetNotMaxGradeAbilCount() > 0)
					{
						if (Utils::RollTheDice(LEVELUP_PROBABILITY)) // Increase Level 
						{
							type = UpgradeType::LevelUp;
							SelectLevelUpAbility(abilityInfo);

						}
						else // Upgrade Grade
						{
							type = UpgradeType::GradeUp;
							SelectGradeUpAbility(abilityInfo);
						}
					}else if (abilMgr->GetNotMaxLvlAbilCount() < 0)
					{
						type = UpgradeType::GradeUp;
						SelectGradeUpAbility(abilityInfo);
					}
					else
					{
						type = UpgradeType::LevelUp;
						SelectLevelUpAbility(abilityInfo);
					}
				}
			}
			//GetNewAbility

		}
		else
		{
			if (abilMgr->GetNotMaxLvlAbilCount() > 0 && abilMgr->GetNotMaxGradeAbilCount() > 0)
			{
				if (Utils::RollTheDice(LEVELUP_PROBABILITY)) // Increase Level 
				{
					type = UpgradeType::LevelUp;
					SelectLevelUpAbility(abilityInfo);
				}
				else // Upgrade Grade
				{
					type = UpgradeType::GradeUp;
					SelectGradeUpAbility(abilityInfo);
				}
			}else if (abilMgr->GetNotMaxLvlAbilCount() < 0)
			{
				type = UpgradeType::LevelUp;
				SelectGradeUpAbility(abilityInfo);
			}
			else
			{
				type = UpgradeType::GradeUp;
				SelectLevelUpAbility(abilityInfo);
			}
		}
		auto it = std::find(selectedList.begin(), selectedList.end(), abilityInfo["name"]);
		if (it == selectedList.end() && !abilityInfo.empty() && !abilityInfo["name"].empty())
		{
			selectedSkill.push_back({ abilityInfo, type });
			selectedList.push_back(abilityInfo["name"]);
		}
		
		if (selectedSkill.size() == 3)
		{
			flag = false;
		}
	}
	uiAbilSelect->SetPanelStatus(selectedSkill);

}

void GameMgr::SelectNewAbility(json& j)
{
	if (abilMgr->GetRemainRegularAbilityCount() == 0)
	{
		std::string abil = abilMgr->GetRandomRemainAbility(true);
		j = MakeAbilityInfo(abil, AbilityGrade::Legend);
		return;
	}
	else if (abilMgr->GetRemainLegendaryAbilityCount() == 0)
	{
		std::string abil = abilMgr->GetRandomRemainAbility(false);
		std::vector<float> probability = { NOVICE_PROBABILITY, ADEPT_PROBABILITY,
		EXPERT_PROBABILITY , MASTER_PROBABILITY };
		AbilityGrade result = (AbilityGrade)Utils::RandomByWeight(probability);
		j = MakeAbilityInfo(abil, result);
		return;
	}
	std::vector<float> probability = { 1 - LEGEND_PROBABILITY ,LEGEND_PROBABILITY };
	int result = Utils::RandomByWeight(probability);
	if (result == 0)
	{
		std::string abil = abilMgr->GetRandomRemainAbility(false);
		std::vector<float> probability = { NOVICE_PROBABILITY, ADEPT_PROBABILITY,
		EXPERT_PROBABILITY , MASTER_PROBABILITY };
		AbilityGrade result = (AbilityGrade)Utils::RandomByWeight(probability);
		j = MakeAbilityInfo(abil, result);
	}
	else
	{
		std::string abil = abilMgr->GetRandomRemainAbility(true);
		j = MakeAbilityInfo(abil, AbilityGrade::Legend);
	}
}

void GameMgr::SelectLevelUpAbility(json& j)
{
	Ability abil = abilMgr->GetRdNotMaxLvlAbil();

	j = MakeAbilityInfo(abil, UpgradeType::LevelUp);


}

void GameMgr::SelectGradeUpAbility(json& j)
{
	Ability abil = abilMgr->GetRdNotMaxGradeAbil();
	j = MakeAbilityInfo(abil, UpgradeType::GradeUp);
}

void GameMgr::AbilitySelected(int num)
{
	json info = selectedSkill[num].first;
	UpgradeType type = selectedSkill[num].second;

	if (type == UpgradeType::Earn)
	{
		abilMgr->AddAbility(info["name"]);
		AbilityGrade grade = (AbilityGrade)info["grade"];
		if (grade != AbilityGrade::Novice)
		{
			info["grade"] = --grade;
			abilMgr->ChangeAbility(info, UpgradeType::GradeUp);
		}
	
	}
	else
	{
		abilMgr->ChangeAbility(info, type);
	}
	beforeStatus = Status::SELECT_SKILL;
	currentStatus = Status::IDLE;
	FRAMEWORK.SetTimeScale(1.0f);

}

void GameMgr::IncreaseEXP()
{
	player->SetLevel(GEM_EXP);
}
