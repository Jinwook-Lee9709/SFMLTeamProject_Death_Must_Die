#include "stdafx.h"
#include "Player.h"
#include "MonsterProjectile.h"

MonsterProjectile::MonsterProjectile(const std::string& name)
{
}

void MonsterProjectile::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position + sf::Vector2f(0.f, 0.f));
	hitbox.rect.setPosition(position);
}

void MonsterProjectile::SetRotation(float degree)
{
	rotation = degree;
	sprite.setRotation(rotation);
	hitbox.rect.setRotation(rotation);
}

void MonsterProjectile::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(this->scale);
	hitbox.rect.setScale(this->scale);
}

void MonsterProjectile::Reset()
{
	animator.SetTarget(&sprite);
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
	sf::Transformable tr;

	tr.setPosition(position);
	tr.rotate(rotation);
	tr.scale(scale);
	this->hitbox.UpdateTr(tr, { 0, 0, 200, 120 });
	Utils::SetOrigin(hitbox.rect, Origins::MC);
}

void MonsterProjectile::Release()
{
}

void MonsterProjectile::Update(float dt)
{
	if (active)
	{
		sf::Vector2f dir = Utils::AngleToVector(rotation);
		position += dir * info.speed * dt;
		SetPosition(position);
	}
	animator.Update(dt);
	if (!animator.IsPlay())
	{
		active = false;
	}
}

void MonsterProjectile::FixedUpdate(float dt)
{
	if (active)
	{
		sf::RectangleShape playerRect = player->GetHitBox().rect;
		if (Utils::CheckCollision(hitbox.rect, playerRect))
		{
			player->Damage(info.damage);
			this->active = false;
		}
	}
	
}

void MonsterProjectile::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (Variables::isDrawHitBox)
	{
		hitbox.Draw(window);
	}
}

void MonsterProjectile::SetInfo(const json& j)
{
	info = j;
}

void MonsterProjectile::Activate()
{
	active = true;
	animator.Play(info.AnimId);
	Utils::SetOrigin(sprite, Origins::MC);
	this->SetScale(sf::Vector2f{1.f, 1.f} * info.AnimSize);
}
