#include "stdafx.h"
#include "AniSlime.h"
#include "Player.h"

AniSlime::AniSlime(const std::string& name)
	: Monster(name)
{
	Anim.SetTarget(&body);

}

void AniSlime::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sortingY = position.y;
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
	Monster::Reset();

	hitbox.rect.setSize({ 40, 120 });
	hitbox.rect.setPosition({ position });
	hitbox2.rect.setSize({ 20, 60 });
	hitbox2.rect.setPosition(position);
	Utils::SetOrigin(hitbox.rect, Origins::BC);
	Utils::SetOrigin(hitbox2.rect, Origins::BC);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	hp = info.hp;
	HPBar.setScale({ 1.0f, 1.0f });

	attackArea.setTexture(TEXTURE_MGR.Get("resource/texture/Sprite/Warn_PointCast_Spr.png"));
	attackArea.setColor(sf::Color(255, 0, 0, 70));
	Utils::SetOrigin(attackArea, Origins::MC);
	attackArea.setScale({ 1.5f, 1.5f });

	Anim.Play(info.walkAnimId);
	currentStatus = SlimeStatus::Move;

	isDebuff = false;
	isDeath = false;

	tickTimer = 0.f;
	tickInterval = 1.f;
	tickDuration = 6.f;
	tickDamage = 10.f;

	atkTimer.SetDefaultDuration(1.0f);

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void AniSlime::Update(float dt)
{
	SetOrigin(Origins::BC);

	Anim.Update(dt);

	if(isGetHit)
	{
		hitTime += dt;
	}

	sf::Vector2f slimePos = body.getPosition();
	attackArea.setPosition(slimePos);

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
	case SlimeStatus::GetHit:
	{
		GetHitUpdate(dt);
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
	attackDelay += dt;
	opacity = 70.f;
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (Utils::Magnitude(playerPos) < DISTANCE_TO_PLAYER && attackDelay >= attackDuration)
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
		atkTimer.StartTimer(false);
		beforeStatus = currentStatus;
		currentStatus = SlimeStatus::Attack;
		return;
	}
}

void AniSlime::AttackUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (opacity < 255)
	{
		opacity += opacitySpeed * dt;
		if (opacity > 255)
		{
			opacity = 255;
		}
	}

	attackArea.setColor(sf::Color(255, 0, 0, opacity));

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
		isAttack = false;
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = SlimeStatus::Move;
	}
}

void AniSlime::GetHitUpdate(float dt)
{
	if (hitTime >= hitDuration)
	{
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = SlimeStatus::Move;
		isGetHit = false;
		hitTime = 0.f;
	}

	if (hp <= 0)
	{
		hp = 0;
		HPBar.setScale({ 0.f, 0.f });
		Anim.Play(info.deathAnimId);
		beforeStatus = currentStatus;
		isDeath = true;
		currentStatus = SlimeStatus::Death;
	}
}

void AniSlime::DeathUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	isAttack = false;

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

void AniSlime::FixedUpdate(float dt)
{
	if (currentStatus == SlimeStatus::Move)
	{
		Monster::HandleOverlap(dt);
		SetPosition(position);
	}

	if (atkTimer.UpdateTimer(dt))
	{
		if (currentStatus != SlimeStatus::Death)
		{
			sf::FloatRect rect = player->GetHitBox().rect.getGlobalBounds();
			if (Utils::CheckCollision(position, sf::Vector2f(96.f, 96.f), rect))
			{
				player->Damage(info.damage);
			}
		}
	}

}

void AniSlime::Draw(sf::RenderWindow& window)
{
	if (isAttack)
	{
		window.draw(attackArea);
	}
	window.draw(body);
	Monster::Draw(window);
}

void AniSlime::SetInfo(const json& j)
{
	info = j;
	hp = info.hp;
	Anim.Play(info.walkAnimId);
}

void AniSlime::Walk(float dt)
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

void AniSlime::OnAttack()
{

}

void AniSlime::OnHit(float damage)
{
	if (currentStatus == SlimeStatus::Death)
		return;

	beforeStatus = currentStatus;
	currentStatus = SlimeStatus::GetHit;

	isGetHit = true;
	hp -= damage;

	HPBar.setScale({ hp / info.hp, 1.0f });

	SOUND_MGR.PlaySfx(GET_SOUND("slimeHit"));
	Monster::OnHit(damage);
}
