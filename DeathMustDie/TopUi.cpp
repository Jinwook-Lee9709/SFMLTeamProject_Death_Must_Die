#include "stdafx.h"
#include "TopUi.h"
#include "SceneDev1.h"
#include "SceneGame.h"
#include "Structure.h"
#include "Player.h"

TopUi::TopUi(const std::string& name)
	: GameObject(name)
{
}

void TopUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TopUi::SetRotation(float angle)
{
	rotation = angle;
}

void TopUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TopUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void TopUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TopUi::Init()
{
	RES_TABLE_MGR.LoadScene("UI");
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	animator.SetTarget(&aniSpr);
	animator2.SetTarget(&aniSpr2);
	animator3.SetTarget(&aniSpr3);
	animator4.SetTarget(&aniSpr4);

}

void TopUi::Release()
{
}

void TopUi::Reset()
{
	scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	objList = scene->GetObjList();
	

	animator.Play(clipId);
	animator.Stop();
	animator2.Play(clipId2);
	animator2.Stop();
	animator3.Play(clipId3);
	animator3.Stop();
	animator4.Play(clipId4);
	animator4.Stop();

	Utils::SetOrigin(aniSpr, Origins::MC);
	aniSpr.setPosition({ winSize.x * 0.5f, 250.f });
	aniSpr.setScale({ 3.f, 3.f });

	Utils::SetOrigin(aniSpr2, Origins::MC);
	aniSpr2.setPosition({ winSize.x * 0.5f - 20.f, 250.f });
	aniSpr2.setScale({ 3.f, 3.f });

	Utils::SetOrigin(aniSpr3, Origins::MC);
	aniSpr3.setPosition({ winSize.x * 0.5f, 245.f });
	aniSpr3.setScale({ 3.f, 3.f });

	Utils::SetOrigin(aniSpr4, Origins::MC);
	aniSpr4.setPosition({ winSize.x * 0.5f, 245.f });
	aniSpr4.setScale({ 3.f, 3.f });
	
	death = TextGo("PtSerifRegular_Font");
	death.Reset();
	death.SetOrigin(Origins::MC);
	death.SetString(L"DEATH");
	death.SetCharacterSize(50);
	death.SetFillColor(sf::Color(201,65,74));
	death.SetPosition({ aniSpr.getPosition().x - 20.f, aniSpr.getPosition().y - 50.f });

	rect.setSize({ 0.f, 0.f });
	isPlay = false;
	trans = 0;
	dieTimer = 0;

	SetTimer();
	SetMiniMap();
	SetBossHpBar();
	EVENT_HANDLER.AddEventInt("OnBossHit", std::bind(&TopUi::UpdateBossHpBar, this, std::placeholders::_1));
}

void TopUi::Update(float dt)
{
	if (player->GetIsDead())
	{
		
		if (isPlay)
			dieTimer += dt;
		if (dieTimer > 2.f)
		{
			player->Invisible();
			if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
				SCENE_MGR.ChangeScene(SceneIds::Game);
		}
			
		GameOver();
		animator.Update(dt);
		animator2.Update(dt);
		animator3.Update(dt);
		animator4.Update(dt);

		
		sf::Vector2f newPos1 = aniSpr3.getPosition();
		newPos1 = sf::Vector2f(newPos1.x + 90.f * dt, 245.f );
		aniSpr3.setPosition(newPos1);

		sf::Vector2f newPos2 = aniSpr4.getPosition();
		newPos2 = sf::Vector2f(newPos2.x - 90.f * dt, 245.f);
		aniSpr4.setPosition(newPos2);
		if (aniSpr3.getPosition().x > winSize.x * 0.5f + 300.f)
		{
			newPos1.x = winSize.x * 0.5f + 300.f;
			aniSpr3.setPosition(newPos1);
		}
		if (aniSpr4.getPosition().x < winSize.x * 0.5f - 300.f)
		{
			newPos2.x = winSize.x * 0.5f - 300.f;
			aniSpr4.setPosition(newPos2);
		}

		return;
	}
	sec += dt;
	if (sec >= 60)
	{
		minute++;
		sec = 0;
	}

	//animator.Update(dt);
	//animator2.Update(dt);
	//animator3.Update(dt);
	//animator4.Update(dt);

	SetTime(minute, sec);
	SetObjPos();
}

void TopUi::Draw(sf::RenderWindow& window)
{
	if (player->GetIsDead())
	{
		window.draw(rect);
		if (isPlay)
		{
			window.draw(aniSpr);
			if (animator2.IsPlay())
			{
				window.draw(aniSpr2);
			}
			if (!animator2.IsPlay())
			{
				death.Draw(window);
			}
			window.draw(aniSpr3);
			window.draw(aniSpr4);
			
		}
		return;
	}
		
	timer.Draw(window);
	time.Draw(window);

	
	miniMapBack.Draw(window);
	miniMap.Draw(window);
	
	for (auto obj : markerObj)
	{
		obj.Draw(window);
	}
	markerPlayer.Draw(window);

	if (bossHp.IsActive())
	{
		bossHp.Draw(window);
		bossHpFrame.Draw(window);
	}

	/*window.draw(aniSpr);
	window.draw(aniSpr2);
	window.draw(aniSpr3);
	window.draw(aniSpr4);*/
}

void TopUi::SetTimer()
{
	minute = 0;
	sec = 0;

	timer = SpriteGo("timer");
	time = TextGo("PtSerifRegular_Font");
	timer.Reset();
	time.Reset();

	timer.SetOrigin(Origins::TC);
	timer.SetPosition({ winSize.x * 0.5f, 0.f });
	
	time.SetOrigin(Origins::MC);
	time.SetPosition({ timer.GetPosition().x, timer.GetPosition().y + timer.GetGlobalBounds().height * 0.5f});
	time.SetCharacterSize(27);

	timer.SetScale({ 3.f,3.f });

	SetTime(minute, sec);
}

void TopUi::SetTime(float min, float sec)
{

	if (sec < 10)
		time.SetString(std::to_wstring((int)minute) + L":0" + std::to_wstring((int)sec));
	else
		time.SetString(std::to_wstring((int)minute) + L":" + std::to_wstring((int)sec));
	//time.SetOrigin(Origins::MC);
}

void TopUi::SetMiniMap()
{
	miniMap = SpriteGo("miniMap");
	miniMap.Reset();
	miniMapBack = SpriteGo("miniMapBack");
	miniMapBack.Reset();
	markerPlayer = SpriteGo("markerP");
	markerPlayer.Reset();
	for (int i = 0; i < objList.size(); i++)
	{
		markerObj.push_back(SpriteGo("markerObj"));
		markerObj[i].Reset();
	}

	miniMap.SetOrigin(Origins::TR);
	miniMap.SetPosition({ winSize.x, 0.f });

	miniMapBack.SetOrigin(Origins::MC);
	miniMapBack.SetPosition({ miniMap.GetPosition().x - 115.f, miniMap.GetPosition().y + 110.f});
	miniMapBack.SetFillColor(sf::Color(255, 255, 255, 80));

	markerPlayer.SetOrigin(Origins::MC);
	markerPlayer.SetPosition(miniMapBack.GetPosition());

	for (auto& obj : markerObj)
	{
		obj.SetOrigin(Origins::MC);
		obj.SetScale({ 3.f, 3.f });
	}

	miniMap.SetScale({ 3.f,3.f });
	miniMapBack.SetScale({ 3.f,3.f });
	markerPlayer.SetScale({ 3.f, 3.f });
}

void TopUi::SetBossHpBar()
{
	bossHp = SpriteGo("bossHealthBar");
	bossHp.Reset();
	bossHpFrame = SpriteGo("bossHealthBarFrame");
	bossHpFrame.Reset();
	bossHp.SetPosition({ winSize.x * 0.28f, winSize.y * 0.15f - 10.f });
	bossHpFrame.SetPosition({ winSize.x * 0.5f, winSize.y * 0.15f });

	bossHp.SetScale({3.f, 3.f});
	bossHpFrame.SetScale({ 3.f, 3.f });

	bossHp.SetTextureRect(sf::IntRect{ 0, 0, ((int)(286 * 1.f)), 6 });
	bossHp.SetOrigin(Origins::ML);
	bossHpFrame.SetOrigin(Origins::MC);

	bossHp.SetActive(false);
	bossHpFrame.SetActive(false);

	std::function<void()> func = [&]() { bossHp.SetActive(true);  bossHpFrame.SetActive(true); };
	EVENT_HANDLER.AddEvent("OnBossSummon", func);
	func = [&]() { bossHp.SetActive(false);  bossHpFrame.SetActive(false); };
	EVENT_HANDLER.AddEvent("OnBossDeath", func); 
}

void TopUi::UpdateBossHpBar(int hp)
{
	bossHp.SetTextureRect(sf::IntRect{ 0, 0, ((int)(286 * ((float)hp / 2000))), 6 });
	bossHp.SetOrigin(Origins::ML);
}

void TopUi::SetObjPos()
{
	
	int i = 0;
	for (auto& obj : objList)
	{
		sf::Vector2f mag = obj->GetPosition() - player->GetPosition();
		if (Utils::Magnitude(mag / 10.f) < 90 && !obj->GetIsUsed())
		{
			markerObj[i].SetActive(true);
			markerObj[i].SetPosition(markerPlayer.GetPosition() + mag / 10.f);
			markerObj[i].SetOrigin(Origins::MC);
		}
		else
			markerObj[i].SetActive(false);
		i++;
	}
}

void TopUi::GameOver()
{
	rect.setSize({ winSize.x, winSize.y });
	if (!isPlay)
	{
		trans = Utils::Lerp(trans, 30, FRAMEWORK.GetRealDeltaTime(), false);
		rect.setFillColor(sf::Color(179, 109, 252, trans));
		if (trans >= 28)
		{
			rect.setFillColor(sf::Color(0, 0, 0));
			player->sortingLayer = SortingLayers::UI;
			player->sortingOrder = 100;
			player->SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

			animator.Play(clipId);
			animator2.Play(clipId2);
			animator3.Play(clipId3);
			animator4.Play(clipId4);

			isPlay = true;
		}
	}
}
