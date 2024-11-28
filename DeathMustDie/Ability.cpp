#include "stdafx.h"
#include "Ability.h"

Ability::Ability(const json& info, AttackEntityPoolMgr* pool, const std::string& name)
	:  info(info), entityPool(pool), GameObject(name)
{
	SetSkillInfo();
}

void Ability::Update(float dt)
{
	if (isActive) {
		if (duration == 0) {
			for (int i = 0; i < projectiles; i++) {
				activateFunc(); 
			}
			isActive = false; 
		}
		else {
			timer += dt;
			elapsedTimer += dt;
			if (timer >= interval) {
				timer = 0;  
				for (int i = 0; i < projectiles; i++) {
					activateFunc();
				}
			}
			if (elapsedTimer >= duration) {
				isActive = false;
			}
		}
	}
}

void Ability::SetSkillInfo()
{
	SetActivateFunc();
}

void Ability::SetActivateFunc()
{
	this->type = (AbilityType)info["abilityType"].get<int>();

	if (info.contains("projectiles"))
	{
		projectiles = info["projectiles"].get<int>();
	}
	if (info.contains("duration"))
	{
		duration = info["duration"].get<float>();
		interval = info["interval"].get<float>();
	}

	switch ( (AttackEntityType)info["entityType"].get<int>() )
	{
		case AttackEntityType::Fall:
		{
			entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
			activateFunc = [&]() {
				AttackEntity* entity = entityPool->GetEntity(name);
				sf::Vector2f pos = WORLD_MOUSE_POS + sf::Vector2f(Utils::RandomRange(0, 200), Utils::RandomRange(0, 200));
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
		case AttackEntityType::Trail:
		{
			entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
			activateFunc = [&]() {
				AttackEntity* entity = entityPool->GetEntity(name);
				sf::Vector2f pos = WORLD_MOUSE_POS + sf::Vector2f(Utils::RandomRange(0, 200), Utils::RandomRange(0, 200));
				entity->SetPosition(pos);
				entity->Activate();
				};
			break;
		}
	}

}

void Ability::UseAbility()
{
	elapsedTimer = 0;
	timer = 0;
	isActive = true;
}

