#include "stdafx.h"
#include "AniSlime.h"

AniSlime::AniSlime(const std::string& name)
	: Monster(name)
{
	walkAnim.SetTarget(&body);
	attackAnim.SetTarget(&body);
}

void AniSlime::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
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
	Walk();
}

void AniSlime::Update(float dt)
{
	SetOrigin(Origins::BC);

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

	walkAnim.Update(dt);
	attackAnim.Update(dt);

	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		speed = 0.f;
		OnAttack();
	}
}

void AniSlime::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniSlime::SetInfo(const json& j)
{
	info = j;
}

void AniSlime::Walk()
{
	if (!attackAnim.IsPlay())
	{
		active = true;
		speed = 70.f;
		walkAnim.Play(info.walkAnimId);
	}
}

void AniSlime::OnAttack()
{
	active = true;
	attackAnim.Play(info.attackAnimId);
}