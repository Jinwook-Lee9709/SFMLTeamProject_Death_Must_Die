#include "stdafx.h"
#include "AniSkeleton.h"

AniSkeleton::AniSkeleton(const std::string& name)
	: Monster(name)
{
	walkAnim.SetTarget(&body);
	attackAnim.SetTarget(&body);
	deathAnim.SetTarget(&body);
}

void AniSkeleton::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
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
	attackRange.setFillColor(sf::Color::White);
	attackRange.setRadius(50.f);
}

void AniSkeleton::Release()
{
}

void AniSkeleton::Reset()
{
	Walk();
}

void AniSkeleton::Update(float dt)
{
	SetOrigin(Origins::BC);

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f monsterPos = body.getPosition();

	/*if (Utils::Distance(position, (sf::Vector2f)mousePos) > 10)
	{
		direction = Utils::GetNormal((sf::Vector2f)mousePos - position);
		SetPosition(position + direction * speed * dt);
	}*/

	walkAnim.Update(dt);
	attackAnim.Update(dt);

	sf::FloatRect skeletonBound = body.getGlobalBounds();

	hitbox.UpdateTr(body, skeletonBound);
}

void AniSkeleton::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);

	if (isAttack)
	{
		window.draw(attackRange);
	}
}

void AniSkeleton::SetInfo(const json& j)
{
	info = j;
}

void AniSkeleton::Walk()
{
	active = true;
	speed = 70.f;
	walkAnim.Play(info.walkAnimId);
}

void AniSkeleton::OnAttack()
{
	isAttack = true;
	speed = 0.f;
	attackAnim.Play(info.attackAnimId);

	sf::Vector2f slimePos = body.getPosition();

	if (!walkAnim.IsPlay() && !attackAnim.IsPlay())
	{
		isAttack = false;
		attackRange.setPosition(slimePos);
		Reset();
	}
}

void AniSkeleton::Die()
{
	speed = 0.f;
	deathAnim.Play(info.deathAnimId);
}
