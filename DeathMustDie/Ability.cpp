#include "stdafx.h"
#include "Ability.h"
#include "Player.h"
#include "CalculatorMgr.h"

Ability::Ability(const json& info, AttackEntityPoolMgr* pool, const std::string& user, const std::string& name)
	:  info(info), entityPool(pool), userName(user), GameObject(name)
{
	this->user = SCENE_MGR.GetCurrentScene()->FindGo(userName);
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
	entityPool->CreatePool(name, info["entityType"], info["AttackEntity"], userName);
	/*switch ((AttackEntityType)info["entityType"].get<int>())
	{
	case AttackEntityType::Fall:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"], userName);
		break;
	}
	case AttackEntityType::Wedge:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"], userName);
		break;
	}
	case AttackEntityType::Trail:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"], userName);
		break;
	}
	case AttackEntityType::BasicAttack:
	{
		entityPool->CreatePool(name, info["entityType"], info["AttackEntity"], userName);
		break;
	}
	}*/
}

void Ability::SetInstantiateFunc()
{
	instantiateFunc = [&]()->AttackEntity* {
		return entityPool->GetEntity(name, userName);
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
	case AbilitySpawnType::UserToMouse:
	{
		spawnFunc = [&](AttackEntity* entity) {
			sf::Vector2f mPos = WORLD_MOUSE_POS;
			sf::Vector2f center = user->GetPosition();
			sf::Vector2f dir = mPos - center;
			float angle = Utils::Angle(dir);

			entity->SetPosition(center);
			entity->SetRotation(angle);
			entity->Activate();
			};
		break;
	}
	case AbilitySpawnType::OnUser:
	{
		spawnFunc = [&](AttackEntity* entity) {
			sf::Vector2f pos = user->GetPosition() + sf::Vector2f(0.f, 70.f);
			entity->SetPosition(pos);
			entity->Activate();
			};
		break;
	}
	case AbilitySpawnType::ClosestEnemy:
	{
		spawnFunc = [&](AttackEntity* entity) {
			auto& monsters = ((MonsterPoolManager*)SCENE_MGR.GetCurrentScene()->FindGo("monsterPoolMgr"))->GetMonsterList();
			if (monsters.empty())
				return;
			sf::Vector2f pos = user->GetPosition();

			float distance = 10000;
			Monster* closestMonster = nullptr;
			for (auto& pair : monsters)
			{
				for (auto& monster : pair.second)
				{
					float distanceBuf = Utils::Magnitude(monster->GetPosition() - pos);
					if (distanceBuf < distance)
					{
						distance = distanceBuf;
						closestMonster = monster;
					}
				}
			}
			sf::Vector2f mPos = closestMonster->GetPosition();

			sf::Vector2f dir = mPos - pos;
			float angle = Utils::Angle(dir);

			entity->SetPosition(pos);
			entity->SetRotation(angle);
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

void Ability::ChangeInfo(const json& j)
{
	json originalJson = info;
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (originalJson["ChangeableValue"].contains(it.key()))
		{
			originalJson["ChangeableValue"][it.key()] = it.value();
		}
	}
	info = originalJson;
}

void Ability::SetLevel(int level)
{
	this->level = level;
}