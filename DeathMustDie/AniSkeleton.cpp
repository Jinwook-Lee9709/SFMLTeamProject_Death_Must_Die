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
	HPBar.setPosition({ position.x, position.y - 140 });
	HPBarFrame.setPosition({ position.x, position.y - 140 });
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

	HPBar.setPosition({ position.x, position.y - 140 });
	HPBarFrame.setPosition({ position.x, position.y - 140 });

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

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
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (Utils::Magnitude(playerPos) < DISTANCE_TO_PLAYER)
	{
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

}

void AniSkeleton::DeathUpdate(float dt)
{

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
	hp -= damage;
	Anim.Play(info.getHitAnimId);
	if (!Anim.IsPlay())
	{
		Anim.SetEnd();
	}
	else if (Anim.IsEnd())
	{

	}
	if (hp < 0)
	{
		hp = 0;
		//Die()
	}
}

void AniSkeleton::OnDie()
{
	Anim.Play(info.deathAnimId);
	if (!Anim.IsPlay())
	{
		Anim.SetEnd();
	}
	else if (Anim.IsEnd())
	{
		isDead = true;
		active = false;
	}
}
