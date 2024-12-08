#include "stdafx.h"
#include "Structure.h"
#include "Player.h"
#include "ButtonUi.h"
#include "StatusUi.h"

Structure::Structure(const std::string& name)
	: GameObject(name)
{
}

void Structure::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sortingY = body.getGlobalBounds().top + body.getGlobalBounds().height;
	
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
	body.setTexture(TEXTURE_MGR.Get(bodySpr), true);
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	Utils::SetOrigin(body, Origins::MC);
	body.setScale({ 3.f, 3.f });
	SetKind(kind);
	SetPosition(position);
}

void Structure::Update(float dt)
{
	temp.setSize({ collision.width, collision.height });
	temp.setPosition({ collision.left, collision.top });

	ShowInteract();
}

void Structure::FixedUpdate(float dt)
{
	
	sf::RectangleShape playerArea = player->GetShadow().GetHitBox().rect;
	sf::FloatRect rect = playerArea.getGlobalBounds();
	sf::Vector2f pPos = player->GetPosition();
	sf::Vector2f direction = position - player->GetPosition();
	if (Utils::CheckCollision(temp, playerArea))
	{
		if (direction.x > 0)
		{
			pPos.x -= (rect.left + rect.width - collision.left) - 10.f;
			player->SetPosition(pPos);
		}
		else if (direction.x < 0)
		{
			pPos.x += (collision.left + collision.width - rect.left);
			player->SetPosition(pPos);
		}
		else if (direction.y < 0)
		{
			pPos.y += (collision.top + collision.height - rect.top);
			player->SetPosition(pPos);
		}
		else if (direction.y > 0)
		{
			pPos.y -= (rect.top + rect.height - collision.top);
			player->SetPosition(pPos);
		}
	}
}

void Structure::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	/*window.draw(temp);*/
}

void Structure::SetKind(Kinds kind)
{
	switch (kind)
	{
	case Structure::Kinds::Greed:
		this->kind = kind;
		bodySpr = "resource/texture/Sprite/Object/Obelisk_Greed_Base_Spr.png";
		collision = { position.x - body.getGlobalBounds().width * 0.5f, position.y + 30.f,
			body.getGlobalBounds().width * 0.8f, body.getGlobalBounds().height * 0.3f };
		break;
	case Structure::Kinds::Bookshelf:
		this->kind = kind;
		bodySpr = "resource/texture/Sprite/Object/Bookshelf_WoodenSimple_Base_Spr.png";
		collision = { position.x - body.getGlobalBounds().width * 0.4f, position.y,
			body.getGlobalBounds().width * 0.8f, body.getGlobalBounds().height * 0.5f };
		break;
	case Structure::Kinds::Coffin:
		this->kind = kind;
		bodySpr = "resource/texture/Sprite/Object/Coffin_StoneScripted1_Spr_0001.png";
		collision = { position.x - body.getGlobalBounds().width * 0.5f + 20.f, position.y,
			body.getGlobalBounds().width - 40.f, body.getGlobalBounds().height * 0.5f };
		temp.setRotation(-30);
		break;
	case Structure::Kinds::Sanctuary:
		this->kind = kind;
		bodySpr = "resource/texture/Sprite/Object/Obelisk_Sanctuary_Base_Spr.png";
		collision = { position.x - body.getGlobalBounds().width * 0.5f + 10.f, position.y + 30.f,
			body.getGlobalBounds().width * 0.8f, body.getGlobalBounds().height * 0.3f };
		break;
	case Structure::Kinds::Mineral:
		this->kind = kind;
		bodySpr = "resource/texture/Sprite/Object/MineralSpring_Base_Spr.png";
		collision = { position.x - body.getGlobalBounds().width * 0.5f + 20.f, position.y,
			body.getGlobalBounds().width * 0.7f, body.getGlobalBounds().height * 0.5f };
		break;
	default:
		break;
	}
}

void Structure::ShowInteract()
{
	StatusUi* ui = dynamic_cast<StatusUi*>(SCENE_MGR.GetCurrentScene()->FindGo("UI"));
	float mag = Utils::Magnitude(position - player->GetPosition());
	if (mag < 200.f)
		isInteract = true;
	else
		isInteract = false;

	if (isInteract)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::E) && !isUsed)
		{
			switch (kind)
			{
			case Structure::Kinds::Greed:
				player->SetDashCharge(1);
				break;
			case Structure::Kinds::Bookshelf:
				player->SetLevel(5);
				break;
			case Structure::Kinds::Coffin:
				player->SetDefence(5);
				break;
			case Structure::Kinds::Sanctuary:
				player->SetMaxHp(10);
				break;
			case Structure::Kinds::Mineral:
				player->SetCurHp(10);
				break;
			default:
				break;
			}
			isUsed = true;
		}
	}
}
