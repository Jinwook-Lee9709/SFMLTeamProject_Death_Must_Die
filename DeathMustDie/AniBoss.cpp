#include "stdafx.h"
#include "AniBoss.h"
#include "Player.h"
#include "AttackEntityPoolMgr.h"

AniBoss::AniBoss(const std::string& name)
	:Monster(name)
{
	Anim.SetTarget(&body);
	ParticleAnim.SetTarget(&particleBody);
}

void AniBoss::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	particleBody.setPosition(position);
	circle.setPosition(position);
	hitbox.rect.setPosition(position);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 140 });
}

void AniBoss::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
	particleBody.setRotation(rotation);
}

void AniBoss::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
	particleBody.setScale(scale);
}

void AniBoss::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
		origin = Utils::SetOrigin(particleBody, originPreset);
	}
}

void AniBoss::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
	particleBody.setOrigin(origin);
}

void AniBoss::Init()
{
}

void AniBoss::Release()
{
}

void AniBoss::Reset()
{

	hitbox.rect.setSize({ 40, 120 });
	hitbox.rect.setPosition({ position });
	Utils::SetOrigin(hitbox.rect, Origins::BC);
	HPBar.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 180 });
	HPBarFrame.setPosition({ position.x - HPBar.getSize().x * 0.5f, position.y - 180 });
	Utils::SetOrigin(circle, Origins::MC);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);
	circle.setRadius(5);
	if (player == nullptr)
	{
		player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	}
	hp = info.hp;
	HPBar.setScale({ 1.0f, 1.0f });

	Anim.Play(info.walkAnimId);
	currentStatus = BossStatus::Move;

	isDebuff = false;
	isDeath = false;

	attackDelay = 4.f;

	tickTimer = 0.f;
	tickInterval = 1.f;
	tickDuration = 6.f;
	tickDamage = 10.f;

	json j;
	j["AnimId"] = "sorceror_fireball";
	j["AnimSize"] = 0.4;
	j["damage"] = 2;
	j["speed"] = 500;

	poolMgr = (AttackEntityPoolMgr*)SCENE_MGR.GetCurrentScene()->FindGo("AttackEntityPoolMgr");
	poolMgr->CreatePool("bossProjectile", AttackEntityType::Projectile, j);
	SetRandomPointInCircle();
}

void AniBoss::Update(float dt)
{
	SetOrigin(Origins::BC);

	Anim.Update(dt);
	ParticleAnim.Update(dt);

	sf::Vector2f bossPos = body.getPosition();

	circle.setPosition(bossPos);
	
	if (isArrival)
	{
		SetRandomPointInCircle();
		isArrival = false;
	}

	switch (currentStatus)
	{
	case BossStatus::Move:
	{
		MoveUpdate(dt);
		break;
	}case BossStatus::Attack:
	{
		AttackUpdate(dt);
		break;
	}
	case BossStatus::GetHit:
	{
		GetHitUpdate(dt);
		break;
	}
	case BossStatus::Channel:
	{
		ChannelUpdate(dt);
		break;
	}
	case BossStatus::Death:
	{
		DeathUpdate(dt);
		break;
	}
	}
}

void AniBoss::MoveUpdate(float dt)
{
	Walk(dt);
	attackDelayTimer += dt;
	ParticleAnim.SetEnd();
	attackDelay += dt;
	sf::Vector2f pos = player->GetPosition();

	if (attackDelay >= attackDuration)
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
		attackDelayTimer = 0.f;
		Anim.Play(info.channelAnimId);
		ParticleAnim.Play(info.channelParticleAnimId);
		beforeStatus = currentStatus;
		currentStatus = BossStatus::Channel;
		return;
	}
}

void AniBoss::AttackUpdate(float dt)
{
	if (Utils::RandomValue() < 0.5f)
	{

	}
	else
	{
		FireProjectile();
		isAbilityUsed = true;
	}

	if (!Anim.IsPlay())
	{
		SetIsSummon(false);
		isAbilityUsed = false;
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = BossStatus::Move;
	}
}

void AniBoss::GetHitUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	sf::Vector2f playerPos = player->GetPosition() - position;

	if (hp != 0 && hitCount == 3)
	{
		SetPosition(RandomTPPos());
		hitCount = 0;
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = BossStatus::Move;
	}

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
		currentStatus = BossStatus::Move;
	}

	if (hp < 0)
	{
		hp = 0.f;
		Anim.Play(info.deathAnimId);
		HPBar.setScale({ 0.f, 0.f });
		beforeStatus = currentStatus;

		EVENT_HANDLER.InvokeEvent("OnBossDeath");
		currentStatus = BossStatus::Death;
	}
}

void AniBoss::ChannelUpdate(float dt)
{
	if (Utils::RandomValue() < 0.5f)
	{
		if (!isAbilityUsed)
		{
			OnSummon();
			isAbilityUsed = true;
		}

	}
	else
	{
		if (!isAbilityUsed)
		{
			FireProjectile();
			isAbilityUsed = true;
		}
		
	}



	if (!Anim.IsPlay() && !ParticleAnim.IsPlay())
	{
		isAbilityUsed = false;
		OnSummon();
		//SetPosition(RandomTPPos());
		isAttack = false;
		isFire = false;
		Anim.Play(info.walkAnimId);
		beforeStatus = currentStatus;
		currentStatus = BossStatus::Move;
	}
}

void AniBoss::DeathUpdate(float dt)
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
		isDeath = true;
		Monster::OnDeath();
	}
}

void AniBoss::FixedUpdate(float dt)
{

}

void AniBoss::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(particleBody);
	hitbox.Draw(window);
	Monster::Draw(window);
}

void AniBoss::SetInfo(const json& j)
{
	info = j;
	hp = info.hp;
	Anim.Play(info.walkAnimId);
}

void AniBoss::OnDebuffed(DebuffType types)
{

}

void AniBoss::Walk(float dt)
{
	if (Utils::Magnitude(randomBossPos - position) > 10)
	{
		direction = randomBossPos - position;
		Utils::Normalize(direction);

		SetPosition(position + direction * speed * dt);
	}
	else
	{
		isArrival = true;
	}

	if (position.x > randomBossPos.x)
	{
		SetScale({ -3.f, 3.f });
	}
	else
	{
		SetScale({ 3.f,3.f });
	}
}

void AniBoss::CheckAttack(float dt)
{

}

void AniBoss::OnHit(float damage)
{
	if (currentStatus == BossStatus::Death)
		return;

	Anim.Play(info.getHitAnimId);

	beforeStatus = currentStatus;
	currentStatus = BossStatus::GetHit;

	hitCount++;
	hp -= damage;

	HPBar.setScale({ hp / info.hp, 1.0f });
	Monster::OnHit(damage);

	SOUND_MGR.PlaySfx(GET_SOUND("bossHit"));
	EVENT_HANDLER.InvokeEvent("OnBossHit",(int)hp);

}

void AniBoss::FireProjectile()
{
	sf::Vector2f playerPos = player->GetPosition();
	float centerAngle = Utils::Angle(playerPos - position);
	float angle = centerAngle - 20.f;
	for (int i = 0; i < 5; i++)
	{
		AttackEntity* obj = poolMgr->GetEntity("bossProjectile");
		obj->SetPosition(position);
		obj->SetRotation(angle);
		obj->Activate();
		angle += 10.f;
	}
	SOUND_MGR.PlaySfx(GET_SOUND("fireBlast"));
}

sf::Vector2f AniBoss::RandomTPPos()
{
	float x = 0;
	float y = 0;
	sf::Vector2f playerPos = player->GetPosition();

	randomPosX = std::uniform_real_distribution<float>(playerPos.x - mapBounds.width * 0.5f, playerPos.x + mapBounds.width * 0.5f);
	randomPosY = std::uniform_real_distribution<float>(playerPos.y - mapBounds.height * 0.5f, playerPos.y + mapBounds.height * 0.5f);

	x = randomPosX(rng);
	y = randomPosY(rng);

	sf::Vector2f randomPos = { x, y };

	return randomPos;
}

sf::Vector2f AniBoss::RandomPointInCircle()
{
	sf::Vector2f bossPos = body.getPosition();

	float x = 0;
	float y = 0;

	x = Utils::RandomRange(bossPos.x, circle.getRadius());
	y = Utils::RandomRange(bossPos.y, circle.getRadius());

	return sf::Vector2f(x, y);
}

void AniBoss::SetRandomPointInCircle()
{
	randomBossPos = RandomPointInCircle();
}
