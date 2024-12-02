#include "stdafx.h"
#include "AniSkeleton.h"
#include "Player.h"

AniSkeleton::AniSkeleton(const std::string& name)
	: Monster(name)
{
	Anim.SetTarget(&body);
}

void AniSkeleton::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	hitbox.rect.setPosition(position);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
}

void AniSkeleton::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniSkeleton::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniSkeleton::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniSkeleton::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniSkeleton::Init()
{

}

void AniSkeleton::Release()
{
}

void AniSkeleton::Reset()
{
	hitbox.rect.setSize({ 40, 120 });
	hitbox.rect.setPosition({ position });
	Utils::SetOrigin(hitbox.rect, Origins::BC);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	if (player == nullptr)
	{
		player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	}
	hp = info.hp;
	HPBar.setScale({ 1.0f, 1.0f });

	Anim.Play(info.walkAnimId);
	currentStatus = Status::Move;
}

void AniSkeleton::Update(float dt)
{
	SetOrigin(Origins::BC);

	Anim.Update(dt);

	switch (currentStatus)
	{
	case Status::Move:
	{
		MoveUpdate(dt);
		break;
	}case Status::Attack:
	{
		AttackUpdate(dt);
		break;
	}
	case Status::GetHit:
	{
		GetHitUpdate(dt);
		break;
	}
	case Status::Death:
	{
		DeathUpdate(dt);
		break;
	}
	}
}

void AniSkeleton::MoveUpdate(float dt)
{
	Walk(dt);
	attackDelay += dt;
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (Utils::Magnitude(playerPos) < DISTANCE_TO_PLAYER)
	{
		if (position.x > pos.x)
		{
			Anim.SetFlip(true);
		}
		else
		{
			Anim.SetFlip(false);
		}

		isAttack = true;
		Anim.Play(info.attackAnimId);
		attackDelay = 0.f;
		beforeStatus = currentStatus;
		currentStatus = Status::Attack;
		return;
	}
}

void AniSkeleton::AttackUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (position.x > pos.x)
	{
		Anim.SetFlip(true);
	}
	else
	{
		Anim.SetFlip(false);
	}


	if (!Anim.IsPlay())
	{
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = Status::Move;
		attackDelay = 0.f;
	}
}

void AniSkeleton::GetHitUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (position.x > pos.x)
	{
		Anim.SetFlip(true);
	}
	else
	{
		Anim.SetFlip(false);
	}

	if (isDebuff)
	{
		debuffTimer += dt;

		if (debuffTimer >= debuffInterval)
		{
			hp -= tikDamage;
			debuffTimer = 0.f;
			debuffCount++;
		}
		else if (debuffCount >= 6.f)
		{
			isDebuff = false;
			debuffTimer = 0.f;
		}
	}

	if (!Anim.IsPlay())
	{
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = Status::Move;
	}

	if (hp < 0)
	{
		hp = 0.f;
		Anim.Play(info.deathAnimId);
		HPBar.setScale({ 0.f, 0.f });
		beforeStatus = currentStatus;
		currentStatus = Status::Death;
	}
}

void AniSkeleton::DeathUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (position.x > pos.x)
	{
		Anim.SetFlip(true);
	}
	else
	{
		Anim.SetFlip(false);
	}

	if (!Anim.IsPlay())
	{
		isDead = true;
		Monster::OnDeath();
	}
}

void AniSkeleton::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
	Monster::Draw(window);
}

void AniSkeleton::SetInfo(const json& j)
{
	info = j;
	hp = info.hp;
	Anim.Play(info.walkAnimId);
}

void AniSkeleton::Walk(float dt)
{
	sf::Vector2f playerPos = player->GetPosition();

	if (Utils::Magnitude(playerPos - position) > DISTANCE_TO_PLAYER)
	{
		direction = playerPos - position;
		Utils::Normalize(direction);

		SetPosition(position + direction * speed * dt);
	}

	if (position.x > playerPos.x)
	{
		SetScale({ -3.f, 3.f });
	}
	else
	{
		SetScale({ 3.f,3.f });
	}
}

void AniSkeleton::CheckAttack(float dt)
{
	attackDelay += dt;
	//sf::Vector2f mousePos = scene->ScreenToWorld(InputMgr::GetMousePosition());


	if (Anim.IsEnd())
	{
		isAttack = false;
		currentStatus = Status::Move;
	}
}

void AniSkeleton::OnHit(float damage)
{
	if (currentStatus == Status::Death)
		return;

	Anim.Play(info.getHitAnimId);

	beforeStatus = currentStatus;
	currentStatus = Status::GetHit;

	hp -= damage;

	HPBar.setScale({ hp / info.hp, 1.0f });
}

void AniSkeleton::OnDebuff(float dt)
{
	isDebuff = true;
}
