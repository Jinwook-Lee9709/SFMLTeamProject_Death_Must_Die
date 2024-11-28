#include "stdafx.h"
#include "Ability.h"

Ability::Ability(const json& info, AttackEntityPoolMgr* pool, const std::string& name)
	:  info(info), entityPool(pool), GameObject(name)
{
	SetSkillInfo();
}

void Ability::SetSkillInfo()
{
	SetActivateFunc();
}

void Ability::SetActivateFunc()
{
	switch ( (AttackEntityType)info["entityType"].get<int>() )
	{
		case AttackEntityType::Fall:
		{
			entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
			activateFunc = [&]() {
				AttackEntity* entity = entityPool->GetEntity(name);
				sf::Vector2f pos = WORLD_MOUSE_POS;
				entity->SetPosition(pos);
				entity->Activate();
				};
			break;
		}
		case AttackEntityType::Wedge:
		{
			entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
			activateFunc = [&]() {
				AttackEntity* entity = entityPool->GetEntity(name);
				sf::Vector2f mPos = WORLD_MOUSE_POS;
				sf::Vector2f center = SCENE_MGR.GetCurrentScene()->GetWorldViewCenter();
				sf::Vector2f dir = mPos - center;
				float angle = Utils::Angle(dir);
				entity->SetPosition(center);
				entity->SetRotation(angle);
				entity->Activate();
				};
			break;
		}
	}

}

void Ability::UseAbility()
{
	activateFunc();
}

