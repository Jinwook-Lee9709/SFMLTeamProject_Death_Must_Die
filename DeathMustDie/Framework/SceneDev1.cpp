#include "stdafx.h"
#include "SceneDev1.h"
#include "Player.h"
#include "StatusUi.h"
#include "TopUi.h"
#include "Structure.h"


SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	player = AddGo(new Player("Player"));
	
	AddGo(new StatusUi("UI"));
	AddGo(new TopUi("TopUI"));
	/*for (int i = 0; i < 5; i++)
	{
		SetObjPos();
	}*/
	
;	Scene::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	
}

void SceneDev1::Enter()
{

	player = AddGo(new Player("Player"));

	AddGo(new StatusUi("UI"));
	AddGo(new TopUi("TopUI"));
	RES_TABLE_MGR.LoadScene("Dev1");
	
	Scene::Enter();
	player->SetScale({ 3.f, 3.f });
	sprite = new SpriteGo("background");
	sprite->Reset();
	sprite->SetScale({10.f,10.f});
}

void SceneDev1::Exit()
{
	for (auto stru : struList)
	{
		RemoveGo(stru);
		struPool.Return(stru);
	}
	struList.clear();

	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	sprite->Draw(window);
	Scene::Draw(window);
	
}

void SceneDev1::SetObjPos()
{
	sf::Vector2f posRangeX = { -500.f, 500.f };
	sf::Vector2f posRangeY = { -500.f, 500.f };
	Structure* stru = struPool.Take();
	
	float posX = Utils::RandomRange(posRangeX.x, posRangeX.y);
	float posY = Utils::RandomRange(posRangeY.x, posRangeY.y);
	stru->SetPosition({posX, posY});

	struList.push_back(stru);
	AddGo(stru);
}
