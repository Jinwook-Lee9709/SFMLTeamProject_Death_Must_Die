#include "stdafx.h"
#include "Ability.h"
#include "SummonEntity.h"
#include "Player.h"

SummonEntity::SummonEntity(const std::string& name)
	:AttackEntity()
{
	animator.SetTarget(&sprite);
	SCENE_MGR.GetCurrentScene()->AddGo(this);
	SCENE_MGR.GetCurrentScene()->ApplyAddGo();
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
}

void SummonEntity::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
}

void SummonEntity::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
}

void SummonEntity::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale * info.AnimSize);
}

void SummonEntity::Reset()
{
	timer = 0;
	beforeStatus = Status::Attack;
	currentStatus = Status::Chase;
}

void SummonEntity::Release()
{

}

void SummonEntity::Update(float dt)
{
	attackTimer += dt;
	if (Utils::Magnitude(player->GetPosition() - position) > 2000.f)
	{
		std::cout << Utils::Magnitude(player->GetPosition() - position) <<std::endl;
		currentStatus = Status::ReturnToPlayer;
	}
	switch (currentStatus)
	{
		case Status::Chase:
		{
			UpdateChase(dt);
			break;
		}
		case Status::ReturnToPlayer:
		{
			UpdateReturnToPlayer(dt);
			break;
		}
		case Status::Attack:
		{
			UpdateAttack(dt);
			break;
		}
	}
	
	abil->Update(dt);
	animator.Update(dt);

	if (info.duration > 0)
	{
		timer += dt;
		if (timer > info.duration)
		{
			this->active = false;
		}
	}
}

void SummonEntity::UpdateChase(float dt)
{
	if (target == nullptr)
		FindTarget();

	if (target == nullptr) { return; }

	sf::Vector2f targetPos = target->GetPosition();
	float distance = Utils::Magnitude(targetPos - position);
	if (target != nullptr && distance > info.attackRange)
	{
		sf::Vector2f dir = Utils::GetNormal(targetPos - position);
		position += dir * info.speed * dt;
		SetPosition(position);
	}
	if (distance < info.attackRange && attackTimer > info.attackInterval)
	{
		beforeStatus = Status::Chase;
		currentStatus = Status::Attack;
		attackTimer = 0;
	}
}

void SummonEntity::UpdateAttack(float dt)
{
	abil->UseAbility();
	beforeStatus = Status::Attack;
	currentStatus = Status::Chase;
}

void SummonEntity::UpdateReturnToPlayer(float dt)
{
	sf::Vector2f targetPos = player->GetPosition();
	float distance = Utils::Magnitude(targetPos - position);
	if (player != nullptr)
	{
		sf::Vector2f dir = Utils::GetNormal(targetPos - position);
		position += dir * info.speed * dt;
		SetPosition(position);
	}
	if (distance < info.attackRange)
	{
		beforeStatus = Status::ReturnToPlayer;
		currentStatus = Status::Chase;
		attackTimer = 0;
	}
}

void SummonEntity::FixedUpdate(float dt)
{
	
}

void SummonEntity::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void SummonEntity::SetInfo(const json& j)
{
	info = j;
	AddAbility(j["abilityName"]);
}

void SummonEntity::ChangeInfo(const json& j)
{
	json originalJson = info;
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (originalJson.contains(it.key()))
		{
			originalJson[it.key()] = it.value();
		}
	}
	info = originalJson;

}

void SummonEntity::Activate()
{
	timer = 0;
	animator.Play(info.AnimId);
	Utils::SetOrigin(sprite, Origins::MC);
	SetScale(scale);
}

void SummonEntity::FindTarget()
{

	auto& monsters = ((MonsterPoolManager*)SCENE_MGR.GetCurrentScene()->FindGo("monsterPoolMgr"))->GetMonsterList();
	if (monsters.empty())
		return;
	float distance = 10000;
	target = nullptr;
	for (auto& pair : monsters)
	{
		for (auto& monster : pair.second)
		{
			float distanceBuf = Utils::Magnitude(monster->GetPosition() - position);
			if (distanceBuf < distance)
			{
				distance = distanceBuf;
				target = monster;
			}
		}
	}
	
}

void SummonEntity::AddAbility(const std::string& skillId)
{
	json j = SKILL_TABLE->Get(skillId);
	AttackEntityPoolMgr* entityPool  = (AttackEntityPoolMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AttackEntityPoolMgr");
	abil = new Ability(j, entityPool, name, skillId);
	abil->Reset();
}
