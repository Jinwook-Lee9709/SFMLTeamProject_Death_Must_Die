#include "stdafx.h"
#include "Player.h"
#include "MonsterPoolManager.h"
#include "StatusUi.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	shadow.SetPosition({ position.x, position.y + body.getGlobalBounds().height * 0.5f - 10.f });
	sortingY = shadow.GetPosition().y;
	body.setPosition(position);
	body2.setPosition(position);
	body3.setPosition(position + attackPos);
	body4.setPosition({ position.x, position.y});
	body5.setPosition({ position.x, position.y});
	hitbox.rect.setPosition({position.x, position.y + 15.f});
	backHpBar.setPosition({ position.x,  position.y -body.getGlobalBounds().height * 0.5f + 20.f});
	hpBar.setPosition({ backHpBar.getGlobalBounds().left + 1.f, backHpBar.getGlobalBounds().top + 2.f });
	backDashBar.setPosition({ backHpBar.getPosition().x, backHpBar.getPosition().y - 10.f });
	for (int i = 0; i < curStat.dash.dashCharge; i++)
		dashBlock[i].setPosition({backDashBar.getGlobalBounds().left + 3.f + 7.f * i, backDashBar.getGlobalBounds().top + 2.f});
	damageBar.setPosition(hpBar.getGlobalBounds().left + hpBar.getGlobalBounds().width, hpBar.getGlobalBounds().top);

	
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
	body2.setScale(body2.getScale().x * scale.x, body2.getScale().y * scale.y);
	body3.setScale(body3.getScale().x * scale.x, body3.getScale().y * scale.y);
	body4.setScale(body4.getScale().x * scale.x, body4.getScale().y * scale.y);
	body5.setScale(body5.getScale().x * scale.x, body5.getScale().y * scale.y);
	shadow.SetScale({ shadow.GetScale().x * scale.x, shadow.GetScale().y * scale.y });
	hitbox.rect.setScale(hitbox.rect.getScale().x * scale.x, hitbox.rect.getScale().y * scale.y);
	
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
		body4.setOrigin(body4.getLocalBounds().width * 0.5f + 3.f, body4.getLocalBounds().height - 5.f);
		Utils::SetOrigin(hitbox.rect, Origins::MC);
		shadow.SetOrigin(Origins::BC);
		//Utils::SetOrigin(body2, originPreset);
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
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	LoadStat();
	animator.SetTarget(&body);
	animator2.SetTarget(&body2);
	animator3.SetTarget(&body3);
	animator4.SetTarget(&body4);
	animator5.SetTarget(&body5);
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	RES_TABLE_MGR.LoadAnimation();
	RES_TABLE_MGR.LoadScene("Dev1");
	animator.Play(clipId);
	body.setColor(sf::Color(255, 255, 255, 255));

	animator2.Play(clipId2);
	animator2.Stop();

	animator3.Play(clipId3);
	animator3.Stop();

	animator4.Play(clipId4);
	animator4.Stop();

	animator5.Play(clipId5);
	animator5.Stop();

	body2.setScale(1.f, 1.f);
	body3.setScale(0.2f, 0.2f);
	body3.setPosition(position);
	//body3.setColor(sf::Color::Yellow);
	body4.setScale(0.8f, 0.8f);
	body4.setRotation(-90);
	body5.setScale(1.f, 0.8f);
	Utils::SetOrigin(body5, Origins::MC);
	hitbox.UpdateTr(body, { 0,0,19.f,47.f });
	shadow = SpriteGo("shadow");
	shadow.Reset();
	shadow.SetFillColor(sf::Color::Black);

	dieSprPos.x = body5.getPosition().x + 100.f;

	SetOrigin(Origins::MC);
	
	//Utils::SetOrigin(body4, Origins::BC);
	
	scene = SCENE_MGR.GetCurrentScene();
	ui = dynamic_cast<StatusUi*>(scene->FindGo("UI"));
	SetDashAndHp();
	level = 1;
	exp = 0;
	trans = 255;
	isDead = false;
	ui->UpdateExp(exp, level);
}

void Player::Update(float dt)
{
	animator.Update(dt);
	if (isDead)
	{
		SetStatus(Status::IDLE);
		animator.Stop();
		animator2.Stop();
		animator3.Stop();
		animator4.Stop();
		body.setColor(sf::Color(255, 102, 254));

		
		return;
	}
	
	animator2.Update(dt);
	animator3.Update(dt);
	animator4.Update(dt);
	shadow.GetHitBox().UpdateTr(shadow.GetSprite(), shadow.GetLocalBounds());
	Move(dt);
	Attack(dt);
	Dash(dt);
	UpdateDashCount();
	
	if (InputMgr::GetKeyDown(sf::Keyboard::K))
		Damage(10.f);
	if (InputMgr::GetKeyDown(sf::Keyboard::L))
		SetLevel(5.f);
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad9))
		SetIsDead(true);
	
	if (isDamage)
	{
		damageBarTime += dt;
		if (damageBarTime > 0.1f)
		{
			ui->UpdateTrace();
			damageBar.setSize({ 0.f,0.f });
			damageBarTime = 0;
			isDamage = false;
		}
	}
	if(hp <= 0)
		SetIsDead(true);

	if (direction.x < 0 && (!isAttack || isDash))
	{
		flip = true;
		dashFlip = true;
		animator.SetFlip(true);
		animator2.SetFlip(true);
	}
	else if (direction.x > 0 && (!isAttack || isDash))
	{
		flip = false;
		dashFlip = false;
		animator.SetFlip(false);
		animator2.SetFlip(false);
	}

	if(animator.GetCurrentClipId() != clipId)
		animator.Play(clipId, flip);
}

void Player::Draw(sf::RenderWindow& window)
{
	
	if (animator2.IsPlay())
	{
		window.draw(body2);
		//attackHB.Draw(window);
	}
	if (animator3.IsPlay())
	{
		window.draw(body3);
	}
	if (animator4.IsPlay())
	{
		window.draw(body4);
	}
	if (animator5.IsPlay())
	{
		window.draw(body5);
	}
	hitbox.Draw(window);
	shadow.Draw(window);
	window.draw(body);
	if (!isDead)
	{
		window.draw(backHpBar);
		window.draw(hpBar);
		window.draw(damageBar);
		window.draw(backDashBar);
		for (auto& dashes : dashBlock)
			window.draw(dashes);
	}
}

void Player::SetDashAndHp()
{
	dashCharge = curStat.dash.dashCharge;
	hp = curStat.defensive.life;
	hp = curStat.defensive.life;

	backHpBar.setSize({ 70.f, 7.f});
	backHpBar.setFillColor(sf::Color::Black);
	Utils::SetOrigin(backHpBar, Origins::MC);
	backHpBar.setPosition({ position.x, position.y - 50.f});

	hpBar.setSize({ 68.f, 3.f });
	hpBar.setFillColor(sf::Color(156,3,0));
	hpBar.setPosition({ backHpBar.getGlobalBounds().left, body.getGlobalBounds().top - 2.f});

	backDashBar.setSize({ 4.f + 7.f * dashCharge, 7.f });
	backDashBar.setFillColor(sf::Color::Black);
	Utils::SetOrigin(backDashBar, Origins::MC);
	backDashBar.setPosition({ backHpBar.getPosition().x, backHpBar.getPosition().y - 6.f});

	for (int i = 0; i < dashCharge; i++)
	{
		dashBlock.push_back(sf::RectangleShape({ 5.f,3.f }));
		dashBlock[i].setFillColor(sf::Color(249, 206, 107));
		dashBlock[i].setPosition({ backDashBar.getGlobalBounds().left + 3.f * i, backDashBar.getGlobalBounds().top - 2.f });
	}
	
}

void Player::UpdateDashCount()
{
	int count = curStat.dash.dashCharge;
	for (int i = 0; i < count; i++)
	{
		dashBlock[i].setSize({ 0.f,0.f });
	}
	for (int i = 0; i < dashCharge; i++)
	{
		dashBlock[i].setSize({ 5.f,3.f });
	}
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
		clipId4 = "dash_spr";
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

	if (!isDash)
	{
		if ((InputMgr::GetKey(sf::Keyboard::A) && InputMgr::GetKey(sf::Keyboard::D)))
			direction = { 0, direction.y };
		if ((InputMgr::GetKey(sf::Keyboard::W) && InputMgr::GetKey(sf::Keyboard::S)))
			direction = { direction.x, 0 };
		SetPosition(position + direction * (float)baseStat.defensive.moveSpeed * dt);
	}
	if (!isAttack && !isDash)
	{
		direction.x != 0.f || direction.y != 0.f ? SetStatus(Status::WALK) : SetStatus(Status::IDLE);
	}
}

void Player::Attack(float dt)
{
	attackTerm += dt;
	sf::Vector2f mousePos  = scene->ScreenToWorld(InputMgr::GetMousePosition());
	float directionX;
	
	
	if (dashQueue.empty())
	{
		dashQueue.push(Status::ATTACK);
		dashQueue.push(Status::ATTACK2);
		dashQueue.push(Status::ATTACK);
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && !isDash)
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
		if (attackTerm > baseStat.attack.attackTime)
		{
			
			SetStatus(dashQueue.front());

			animator.Play(clipId, flip);
			if(dashQueue.front() == Status::ATTACK2 && !flip)
				animator3.Play(clipId3, true);
			else if (dashQueue.front() == Status::ATTACK2 && flip)
				animator3.Play(clipId3, false);
			else
				animator3.Play(clipId3, flip);
			animator2.Play(clipId2, flip);
			
			body3.setRotation(Utils::Angle(look) + 90);
			look.x *= 2;
			attackPos = look * 10.f;
			body3.setPosition(position + attackPos);
			attackTerm = 0.f;
			EVENT_HANDLER.InvokeEvent("OnAttack");
			SOUND_MGR.PlaySfx(GET_SOUND("swordSlash"));
			dashQueue.pop();
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
 		while (!dashQueue.empty())
			dashQueue.pop();
	}
	if (animator.IsEnd())
		isAttack = false;
	if (animator2.IsEnd())
	{
	}
}

void Player::Dash(float dt)
{
	if (dashCharge < curStat.dash.dashCharge)
		dashChargeTime += dt;
	if (dashChargeTime > curStat.dash.dashRechargeTime)
	{
		dashCharge++;
		dashChargeTime = 0;
		
	}       
	if ((direction.x == 0.f && direction.y == 0.f && !isDash))
		return;
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		if (dashCharge == 0)
			return;
		isDash = true;
		frame = 0;
		dashCharge--;
		SetStatus(Status::DASH);

		dashDirection = Utils::GetNormal(direction);
		body4.setRotation(Utils::Angle(dashDirection) - 90);

		animator.Play(clipId, flip);
		animator2.Play(clipId2, flip);
		animator4.Play(clipId4, flip);
		
		dashPos = position + dashDirection * 600.f * 0.4f;
		EVENT_HANDLER.InvokeEvent("OnDash");
	}

	if (animator2.IsPlay() && isDash)
	{
		sf::Vector2f newPos = position;
		newPos = Utils::Lerp(newPos, dashPos, dt * 6, true);
		SetPosition(newPos);
	}else
	{
		isDash = false;
	}
}

void Player::SaveStat()
{
	json j = baseStat;
	std::ofstream f("tables/player.json");
	f << j.dump(4) << std::endl;
	f.close();
}

void Player::LoadStat()
{
	std::ifstream f("tables/player.json");
	json j = json::parse(f);
	baseStat.attack = j["attack"];
	baseStat.blessingSlot = j["blessingSlot"];
	baseStat.dash = j["dash"];
	baseStat.defensive = j["defensive"];
	baseStat.godBlessing = j["godBlessing"];
	baseStat.offensive = j["offensive"];
	baseStat.utility = j["utility"];

	curStat = baseStat;
}

Stat& Player::GetStat()
{
	return this->baseStat;
}

Stat& Player::GetCurStat()
{
	return this->curStat;
}

SpriteGo& Player::GetShadow()
{
	return this->shadow;
}

sf::Vector2f Player::GetDirection()
{
	return direction;
}

void Player::SetIsDead(bool dead)
{
	isDead = dead;
}

void Player::ChangeAttackColor(sf::Color color)
{
	body3.setColor(color);
}

void Player::Damage(float damage)
{
	float value = Utils::Clamp(damage - curStat.defensive.armor, 0, hp) / curStat.defensive.life;
	isDamage = true;
	hp = Utils::Clamp(hp - (damage - curStat.defensive.armor), 0, curStat.defensive.life);

	SetHp(hp, value);
	ui->UpdateHp(hp, value);

	/*if (hp == 0) {
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}*/
}

void Player::SetHp(float hp, float damage)
{
	sf::Vector2f maxSize = { 68.f, 3.f };
	damageBar.setSize({ maxSize.x * damage, maxSize.y });
	hpBar.setSize({ maxSize.x * hp / curStat.defensive.life, maxSize.y });
	damageBar.setPosition(hpBar.getGlobalBounds().left + hpBar.getGlobalBounds().width, hpBar.getGlobalBounds().top);
}

void Player::SetLevel(float exp)
{
	this->exp += exp;
	if (this->exp >= EXP_TABLE->Get(level + 1).curExp)
	{
		level++;
		this->exp = 0;
		EVENT_HANDLER.InvokeEvent("LevelUp");
	}
	ui->UpdateExp(this->exp, level);
}

void Player::SetMaxHp(int maxHp)
{
	curStat.defensive.life += maxHp;
	SetCurHp(maxHp);
	ui->UpdateHp(hp);
	ui->UpdateTrace();
}

void Player::SetDashCharge(int count)
{
	curStat.dash.dashCharge += count;
	SetDashAndHp();
	ui->SetStaminaFrame();
}

void Player::SetCurHp(int count)
{
	hp = Utils::Clamp(hp + count,0,curStat.defensive.life);
	SetHp(hp);
	ui->UpdateHp(hp);
	ui->UpdateTrace();
}

void Player::SetDefence(int count)
{
	curStat.defensive.armor += count;
}

void Player::Invisible()
{
	trans = Utils::Lerp(trans, 0, 0.0001f, false);
	body.setColor(sf::Color(255, 255, 255, trans));
}
