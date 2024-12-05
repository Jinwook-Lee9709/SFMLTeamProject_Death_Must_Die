#include "stdafx.h"
#include "SceneGame.h"
#include "AbilityMgr.h"
#include "AniBoss.h"
#include "AttackEntityPoolMgr.h"
#include "CalculatorMgr.h"
#include "GameMgr.h"
#include "ItemPoolManager.h"
#include "ItemSpawner.h"
#include "MonsterSpawner.h"
#include "Player.h"
#include "StatusUi.h"
#include "Structure.h"
#include "TileMap.h"
#include "TopUi.h"
#include "UIAbilitySelect.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	AddGo(new StatusUi("UI"));
	AddGo(new TopUi("TopUI"));
	for (int i = 0; i < 5; i++)
	{
		SetObjPos();
	}

	worldView.setSize(size);
	uiView.setSize(size);
	player = AddGo(new Player("Player"));
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setCenter(0.f, 0.f);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	RES_TABLE_MGR.LoadScene("Game");
	RES_TABLE_MGR.LoadAnimation();


	map = AddGo(new TileMap("map"));
	AddGo(new AttackEntityPoolMgr("AttackEntityPoolMgr"));
	abilMgr = AddGo(new AbilityMgr("AbilityMgr"));
	AddGo(new CalculatorMgr("CalculatorMgr"));
	MPMgr = AddGo(new MonsterPoolManager("monsterPoolMgr"));
	monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 30));
	AddGo(new UIAbilitySelect("UIAbilitySelect"));
	itemMPMgr = AddGo(new ItemPoolManager("itemPoolMgr"));
	itemSpawn = AddGo(new ItemSpawner(itemMPMgr));
	AddGo(new GameMgr("GameMgr"));
	ApplyAddGo();

	Scene::Enter();
	map->SetOrigin(Origins::MC);
	player->SetScale({ 3.f, 3.f });
}

void SceneGame::Exit()
{
	for (auto stru : struList)
	{
		RemoveGo(stru);
		struPool.Return(stru);
	}
	struList.clear();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);
	if (MPMgr)
	{
		MPMgr->CheckCollisions();
	}
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}

void SceneGame::SetObjPos()
{
	sf::Vector2f posRangeX = { -2000.f, 2000.f };
	sf::Vector2f posRangeY = { -2000.f, 2000.f };
	Structure* stru = struPool.Take();

	float posX = Utils::RandomRange(posRangeX.x, posRangeX.y);
	float posY = Utils::RandomRange(posRangeY.x, posRangeY.y);
	stru->SetPosition({ posX, posY });

	struList.push_back(stru);
	AddGo(stru);
}


