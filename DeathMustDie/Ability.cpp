#include "stdafx.h"
#include "Ability.h"
#include "Player.h"
#include "CalculatorMgr.h"

Ability::Ability(const json& info, AttackEntityPoolMgr* pool, const std::string& name)
	:  info(info), entityPool(pool), GameObject(name)
{
}

void Ability::Reset()
{
	SetSkillInfo();
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
	calc = (CalculatorMgr*)SCENE_MGR.GetCurrentScene()->FindGo("CalculatorMgr");
}

void Ability::Update(float dt)
{
	if (isActive) {
		if (duration == 0) {
			for (int i = 0; i < projectiles; i++) {
				AttackEntity* instance = instantiateFunc();
				if (changeInfoFunc) { changeInfoFunc(instance); }
				if (spawnFunc) { spawnFunc(instance); }
			}
			isActive = false; 
		}
		else {
			timer += dt;
			elapsedTimer += dt;
			if (timer >= interval) {
				timer = 0;  
				for (int i = 0; i < projectiles; i++) {
					AttackEntity* instance = instantiateFunc();
					if (changeInfoFunc) { changeInfoFunc(instance); }
					if (spawnFunc) { spawnFunc(instance); }
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
	SetFunc();
}

void Ability::SetFunc()
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
	CreateEntityPool();
	SetInstantiateFunc();
	SetChangeInfoFunc();
	SetSpawnFunc();

}

void Ability::CreateEntityPool()
{
	switch ((AttackEntityType)info["entityType"].get<int>())
	{
	case AttackEntityType::Fall:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
		break;
	}
	case AttackEntityType::Wedge:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
		break;
	}
	case AttackEntityType::Trail:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
		break;
	}
	case AttackEntityType::BasicAttack:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"]);
		break;
	}
	}
}

void Ability::SetInstantiateFunc()
{
	instantiateFunc = [&]()->AttackEntity* {
		return entityPool->GetEntity(name);
		};
}

void Ability::SetChangeInfoFunc()
{
	if (!info.contains("ChangeableValue"))
	{
		return;
	}

	std::unordered_map<std::string, std::function<void(json&)>> handler = 
	{
		{"damage", [&](json& updateJson)
			{
				float damageMultiplyer = info["ChangeableValue"]["damage"].get<float>();
				Stat& stat = player->GetStat();
				float min = calc->GetValue(type, stat.attack.attackDamageMin);
				float max = calc->GetValue(type, stat.attack.attackDamageMax);
				float damage = Utils::RandomRange(min, max);
				damage *= info["ChangeableValue"]["damage"].get<float>();
				updateJson["damage"] = damage;
			}
		}
	};

	for (auto& it : handler)
	{
		if (info["ChangeableValue"].contains(it.first))
		{
			activeHandlers.push_back(it.second);
		}
	}
	changeInfoFunc = [&](AttackEntity* entity) {
	json updateJson;
	for (auto& handler : activeHandlers)
	{
		handler(updateJson);
	}
	entity->ChangeInfo(updateJson);
	};
}

void Ability::SetSpawnFunc()
{
	switch ((AbilitySpawnType)info["spawnType"].get<int>())
	{
	case AbilitySpawnType::OnRandomEnemy:
	{
		spawnFunc = [&](AttackEntity* entity) {
			sf::Vector2f pos = WORLD_MOUSE_POS + sf::Vector2f(Utils::RandomRange(0, 200), Utils::RandomRange(0, 200));
			entity->SetPosition(pos);
			entity->Activate();
			};
		break;
	}
	case AbilitySpawnType::CharacterToMouse:
	{
		spawnFunc = [&](AttackEntity* entity) {
			sf::Vector2f mPos = WORLD_MOUSE_POS;
			sf::Vector2f center = player->GetPosition();
			sf::Vector2f dir = mPos - center;
			float angle = Utils::Angle(dir);

			entity->SetPosition(center);
			entity->SetRotation(angle);
			entity->Activate();
			};
		break;
	}
	case AbilitySpawnType::OnCharacter:
	{
		spawnFunc = [&](AttackEntity* entity) {
			sf::Vector2f pos = player->GetPosition() + sf::Vector2f(0.f, 70.f);
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

