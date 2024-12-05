#include "stdafx.h"
#include "Structure.h"
#include "Player.h"

Structure::Structure(const std::string& name)
	: GameObject(name)
{
}

void Structure::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sortingY = position.y;
	collision = { position.x - body.getGlobalBounds().width * 0.5f, position.y + 30.f, 
		body.getGlobalBounds().width, body.getGlobalBounds().height * 0.3f};
	body.setPosition(position);
}

void Structure::SetRotation(float angle)
{
	rotation = angle;
}

void Structure::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Structure::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Structure::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Structure::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Structure::Release()
{
}

void Structure::Reset()
{
	body.setTexture(TEXTURE_MGR.Get("resource/texture/Sprite/Object/Obelisk_Greed_Base_Spr.png"));
	Utils::SetOrigin(body, Origins::MC);
	body.setScale({ 3.f, 3.f });
}

void Structure::Update(float dt)
{
	temp.setSize({ collision.width, collision.height });
	temp.setPosition({ collision.left, collision.top });

	
	
}

void Structure::FixedUpdate(float dt)
{
	Player* player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sf::RectangleShape playerArea = player->GetShadow().GetHitBox().rect;
	sf::FloatRect rect = playerArea.getGlobalBounds();
	sf::Vector2f pPos = player->GetPosition();
	if (Utils::CheckCollision(temp, playerArea))
	{
		if (rect.left < collision.left)
		{
			pPos.x -= rect.left + rect.width - collision.left;
			player->SetPosition(pPos);
		}
		if (rect.left + rect.width > collision.left + collision.width)
		{
			pPos.x += collision.left + collision.width - rect.left;
			player->SetPosition(pPos);
		}
		if (rect.top < collision.top)
		{
			pPos.y -= rect.top + rect.height - collision.top;
			player->SetPosition(pPos);
		}
		if (rect.top + rect.height > collision.top + collision.height)
		{
			pPos.y += collision.top + collision.height - rect.top;
			player->SetPosition(pPos);
		}

	}
}

void Structure::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(temp);
}
