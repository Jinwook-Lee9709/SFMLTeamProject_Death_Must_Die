#include "stdafx.h"
#include "Ability.h"

Ability::Ability(const AbilityType type, const AbilityGrade& grade, const std::string& name)
	: type(type), grade(grade), GameObject(name)
{
}

void Ability::SetSkillInfo()
{
	switch (action)
	{
		case AbilityAction::Fire:
		{
			
			break;
		}
		case AbilityAction::Random:
		{

			break;
		}
		case AbilityAction::Radial:
		{

			break;
		}
		case AbilityAction::Wedge:
		{

			break;
		}
		case AbilityAction::Chain:
		{

			break;
		}
		case AbilityAction::Summon:
		{

			break;
		}
		case AbilityAction::Buff:
		{

			break;
		}
		case AbilityAction::Shield:
		{

			break;
		}
	}
}

