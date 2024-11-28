#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	body2.setPosition(position);
	body3.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
		Utils::SetOrigin(body2, originPreset);
		//Utils::SetOrigin(body3, Origins::BC);
		body3.setOrigin(body3.getLocalBounds().width * 0.5f, body3.getLocalBounds().height - 50.f);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	SaveStat();
	animator.SetTarget(&body);
	animator2.SetTarget(&body2);
	animator3.SetTarget(&body3);
}

void Player::Release()
{
}

void Player::Reset()
{
	RES_TABLE_MGR.LoadAnimation();
	animator.Play(clipId);
	animator2.Play(clipId2);
	animator3.Play(clipId3);
	body3.setScale(0.2f, 0.2f);
	SetOrigin(Origins::MC);
	attackHB.UpdateTr(body3, body3.getLocalBounds());
	scene = SCENE_MGR.GetCurrentScene();
}

void Player::Update(float dt)
{
	animator.Update(dt);
	animator2.Update(dt);
	animator3.Update(dt);
	Move(dt);
	Attack(dt);
	Dash(dt);
	attackHB.UpdateTr(body3, body3.getLocalBounds());
	
	if (direction.x < 0)
	{
		flip = true;
		animator.SetFlip(true);
		animator2.SetFlip(true);
	}
	else if (direction.x > 0)
	{
		flip = false;
		animator.SetFlip(false);
		animator2.SetFlip(false);
	}

	if(animator.GetCurrentClipId() != clipId)
		animator.Play(clipId, flip);
}

void Player::Draw(sf::RenderWindow& window)
{
	
	if (!animator2.IsEnd())
	{
		window.draw(body2);
		window.draw(body3);
		attackHB.Draw(window);
	}
	window.draw(body);
}

void Player::SetStatus(Status cur)
{
	status = cur;
	switch (status)
	{
	case Player::Status::IDLE:
		clipId = "knight_idle";
		break;
	case Player::Status::WALK:
		clipId = "knight_walk";
		break;
	case Player::Status::DASH:
		clipId = "knight_dash";
		clipId2 = "knight_dash_glow";
		break;
	case Player::Status::ATTACK:
		isAttack = true;
		isAttack2 = true;
		clipId = "knight_attack1";
		clipId2 = "knight_soward1";
		break;
	case Player::Status::ATTACK2:
		isAttack = true;
		isAttack2 = true;
		clipId = "knight_attack2";
		clipId2 = "knight_soward2";
		break;
	default:
		break;
	}
}

void Player::Move(float dt)
{
	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		Utils::Normalize(direction);
	}
	if ((InputMgr::GetKey(sf::Keyboard::A) && InputMgr::GetKey(sf::Keyboard::D)))
		direction = { 0, direction.y };
	if ((InputMgr::GetKey(sf::Keyboard::W) && InputMgr::GetKey(sf::Keyboard::S)))
		direction = { direction.x, 0 };
	SetPosition(position + direction * speed * dt);

	if (!isAttack && !isDash)
	{
		/*if ((direction.x < 0))
		{
			flip = true;
			animator.SetFlip(true);
		}
		else if ((direction.x > 0))
		{
			flip = false;
			animator.SetFlip(false);
		}*/

		direction.x != 0.f || direction.y != 0.f ? SetStatus(Status::WALK) : SetStatus(Status::IDLE);
	}
		

	
}

void Player::Attack(float dt)
{
	attackTerm += dt;
	sf::Vector2f mousePos  = scene->ScreenToWorld(InputMgr::GetMousePosition());
	float directionX;
	
	
	if (temp.empty())
	{
		temp.push(Status::ATTACK);
		temp.push(Status::ATTACK2);
		temp.push(Status::ATTACK);
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		if (mousePos.x < position.x)
		{
			flip = true;
		}
			
		else if (mousePos.x > position.x)
		{
			flip = false;
		}
		sf::Vector2f look = Utils::GetNormal(mousePos - body3.getPosition());
		
		if (attackTerm > stat.attack.attackTime)
		{
			
			SetStatus(temp.front());

			animator.Play(clipId, flip);
			if(temp.front() == Status::ATTACK2 && !flip)
				animator3.Play(clipId3, true);
			else if (temp.front() == Status::ATTACK2 && flip)
				animator3.Play(clipId3, false);
			else
				animator3.Play(clipId3, flip);
			animator2.Play(clipId2, flip);

			body3.setRotation(Utils::Angle(look) + 90);
			
			attackTerm = 0.f;
			temp.pop();
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
 		while (!temp.empty())
			temp.pop();
	}
	if (animator.IsEnd())
		isAttack = false;
	if (animator2.IsEnd())
	{
	}
}

void Player::Dash(float dt)
{
	if (direction.x == 0.f && direction.y == 0.f)
		return;
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isDash = true;
		frame = 0;
		SetStatus(Status::DASH);
		animator.Play(clipId, flip);
		animator2.Play(clipId2, flip);
		dashDirection = direction;
	}

	if (frame <= 40 && isDash)
	{
		SetPosition(position + dashDirection * 500.f * dt);
		frame++;
	}
	if (animator2.IsEnd())
		isDash = false;
	
}

void Player::SaveStat()
{
	json j = stat;
	std::ofstream f("tables/player.json");
	f << j.dump(4) << std::endl;
	f.close();
}

void Player::LoadStat()
{
	std::ifstream f("tables/player.json");
	json j = json::parse(f);
	stat.attack = j["attack"];
	stat.blessingSlot = j["blessingSlot"];
	stat.dash = j["dash"];
	stat.defensive = j["defensive"];
	stat.godBlessing = j["godBlessing"];
	stat.offensive = j["offensive"];
	stat.utility = j["utility"];
}
