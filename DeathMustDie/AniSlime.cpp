#include "stdafx.h"
#include "AniSlime.h"

AniSlime::AniSlime(const std::string& name)
	: Monster(name)
{
	Anim.SetTarget(&body);

}

void AniSlime::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	hitbox.rect.setPosition(position);
	HPBar.setPosition({ position.x, position.y - 140 });
	HPBarFrame.setPosition({ position.x, position.y - 140 });
}

void AniSlime::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniSlime::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniSlime::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniSlime::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniSlime::Release()
{
}

void AniSlime::Reset()
{
	hitbox.rect.setSize({ 40, 120 });
	hitbox.rect.setPosition({ position });
	Utils::SetOrigin(hitbox.rect, Origins::BC);

	HPBar.setPosition({ position.x, position.y - 140 });
	HPBarFrame.setPosition({ position.x, position.y - 140 });
}

void AniSlime::Update(float dt)
{
	SetOrigin(Origins::BC);

	Anim.Update(dt);

	switch (currentStatus)
	{
	case SlimeStatus::Move:
	{
		MoveUpdate(dt);
		break;
	}case SlimeStatus::Attack:
	{
		AttackUpdate(dt);
		break;
	}
	case SlimeStatus::Death:
	{
		DeathUpdate(dt);
		break;
	}
	}
}

void AniSlime::MoveUpdate(float dt)
{
	Walk(dt);

	sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition() - position;

	if (Utils::Magnitude(mousePos) < DISTANCE_TO_PLAYER)
	{
		isAttack = true;
		Anim.Play(info.attackAnimId);
		beforeStatus = currentStatus;
		currentStatus = SlimeStatus::Attack;
		return;
	}
}

void AniSlime::AttackUpdate(float dt)
{
	if (!Anim.IsPlay())
	{
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = SlimeStatus::Move;
	}
}

void AniSlime::DeathUpdate(float dt)
{

}

void AniSlime::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniSlime::SetInfo(const json& j)
{
	info = j;
	hp = info.hp;
	Anim.Play(info.walkAnimId);
}

void AniSlime::Walk(float dt)
{
	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f monsterPos = body.getPosition();

	if (Utils::Distance(position, (sf::Vector2f)mousePos) > 10)
	{
		direction = Utils::GetNormal((sf::Vector2f)mousePos - position);
		SetPosition(position + direction * speed * dt);
	}

	if (monsterPos.x > mousePos.x)
	{
		body.setScale({ -3.f, 3.f });
	}
	else
	{
		body.setScale({ 3.f, 3.f });
	}
}

void AniSlime::OnAttack()
{

}