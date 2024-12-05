#include "stdafx.h"
#include "TopUi.h"
#include "SceneDev1.h"
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
	
}

void TopUi::Release()
{
}

void TopUi::Reset()
{
	scene = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(scene->FindGo("Player"));
	objList = scene->GetObjList();

	SetTimer();
	SetMiniMap();
}

void TopUi::Update(float dt)
{
	sec += dt;
	if (sec >= 60)
	{
		minute++;
		sec = 0;
	}
	SetTime(minute, sec);
	SetObjPos();
}

void TopUi::Draw(sf::RenderWindow& window)
{
	timer.Draw(window);
	time.Draw(window);

	
	miniMapBack.Draw(window);
	miniMap.Draw(window);
	
	for (auto obj : markerObj)
	{
		obj.Draw(window);
	}
	markerPlayer.Draw(window);
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

void TopUi::SetObjPos()
{
	
	int i = 0;
	for (auto& obj : objList)
	{
		sf::Vector2f mag = obj->GetPosition() - player->GetPosition();
		if (Utils::Magnitude(mag / 10.f) < 90)
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
