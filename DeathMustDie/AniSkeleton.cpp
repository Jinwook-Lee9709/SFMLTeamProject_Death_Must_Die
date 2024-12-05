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
	hitbox2.rect.setPosition({ position.x, position.y - 30.f });
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
	hitbox2.rect.setSize({ 20, 60 });
	hitbox2.rect.setPosition(position);
	Utils::SetOrigin(hitbox.rect, Origins::BC);
	Utils::SetOrigin(hitbox2.rect, Origins::BC);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	if (player == nullptr)
	{
		player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	}
	hp = info.hp;
	HPBar.setScale({ 1.0f, 1.0f });

	attackArea.setTexture(TEXTURE_MGR.Get("resource/texture/Sprite/Warn_Melee_Slash_Spr.png"));
	attackArea.setColor(sf::Color( 255, 0, 0, 70));
	Utils::SetOrigin(attackArea, Origins::BC);
	attackArea.setScale({ 0.8f, 0.8f });

	Anim.Play(info.walkAnimId);
	currentStatus = Status::Move;

	isDebuff = false;

	tickTimer = 0.f;
	tickInterval = 1.f;
	tickDuration = 6.f;
	tickDamage = 10.f;
}

void AniSkeleton::Update(float dt)
{
	SetOrigin(Origins::BC);

	sf::Vector2f playerPos = body.getPosition();

	attackArea.setPosition(playerPos);

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
	opacity = 70;
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	look = Utils::GetNormal(pos - position);

	attackArea.setRotation(Utils::Angle(look));

	/*if (player != nullptr && Utils::Distance(position, player->GetPosition()) > 10)
	{
		direction = Utils::GetNormal(player->GetPosition() - position);
		attackArea.setRotation(Utils::Angle(direction));
	}*/

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
		beforeStatus = currentStatus;
		currentStatus = Status::Attack;
		return;
	}
}

void AniSkeleton::AttackUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	opacity += opacitySpeed * dt;

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
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = Status::Move;
		isAttack = false;
		attackDelay = 0.f;
		opacity = 70;
	}
}

void AniSkeleton::GetHitUpdate(float dt)
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
	if (isAttack)
	{
		window.draw(attackArea);
	}
	window.draw(body);
	/*hitbox.Draw(window);
	hitbox2.Draw(window);*/
	Monster::Draw(window);
}

void AniSkeleton::SetInfo(const json& j)
{
	info = j;
	hp = info.hp;
	Anim.Play(info.walkAnimId);
}

void AniSkeleton::OnDebuffed(DebuffType types, float dt)
{
	tickTimer += dt;
	tickDuration -= dt;

	if (tickDuration <= 0)
	{
		isDebuff = false;
		tickTimer = 0.f;
		return; // 디버프 종료
	}

	switch (types)
	{
	case DebuffType::Burn:

		if (tickTimer >= tickInterval)
		{
			tickTimer -= tickInterval;
			hp -= tickDamage;
			HPBar.setScale({ std::max(hp / info.hp, 0.f), 1.0f });
			beforeStatus = currentStatus;
			currentStatus = Status::GetHit;
			/*if (hp <= 0)
			{
				hp = 0;
				beforeStatus = currentStatus;
				currentStatus = Status::Death;
				HPBar.setScale({ 0.f, 0.f });
			}*/
		}


	}
}

void AniSkeleton::Walk(float dt)
{
	sf::Vector2f playerPos = player->GetPosition();

	if (Utils::Magnitude(playerPos - position) > DISTANCE_TO_PLAYER)
	{
		direction = playerPos - position;
		Utils::Normalize(direction);

		/*attackArea.setRotation(Utils::Angle(direction));*/
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
