#include "stdafx.h"
#include "Monster.h"
#include "SceneDev2.h"

Monster::Monster(const std::string& texId, const std::string& name)
	:GameObject(name), textureId(texId)
{
}

void Monster::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Monster::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Monster::SetScale(const sf::Vector2f& size)
{
	scale = size;
	body.setScale(scale);
}

void Monster::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Monster::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Monster::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Monster::GetGlobalBounds() const
{
	return body.getLocalBounds();
}

void Monster::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Monster::Release()
{
}

void Monster::Reset()
{
	body.setTexture(GET_TEX(textureId), true);
	SetOrigin(Origins::BC);
	SetPosition({ 100.f, 100.f });
	SetRotation(0.f);
	SetScale({ 3.f, 3.f });

	player.setSize({ 50.f, 100.f });
	player.setPosition({ 500.f, 500.f });
	Utils::SetOrigin(player, Origins::MC);
}

void Monster::Update(float dt)
{
	sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition();
	sf::Vector2f monsterPos = body.getPosition();
	sf::Vector2f playerPos = player.getPosition();

	if (Utils::Distance(position, playerPos) > 10)
	{
		direction = Utils::GetNormal(playerPos - position);
		SetPosition(position + direction * speed * dt);
	}

	if (monsterPos.x > playerPos.x)
	{
		body.setScale({ -3.f, 3.f });
	}
	else
	{
		body.setScale({ 3.f, 3.f });
	}

	hitbox.UpdateTr(body, GetLocalBounds());
}

void Monster::LateUpdate(float dt)
{
}

void Monster::FixedUpdate(float dt)
{
}

void Monster::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(body);
	}
	window.draw(player);
	hitbox.Draw(window);
}

void Monster::OnAttack()
{
	player.setPosition({ 900.f, 900.f });
}

void Monster::OnDamage()
{
	anim.Play("skeleton_gethit");
}
