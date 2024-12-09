#include "stdafx.h"
#include "SceneGame.h"
#include "AbilityMgr.h"
#include "AniBoss.h"
#include "AttackEntityPoolMgr.h"
#include "CalculatorMgr.h"
#include "DamageText.h"
#include "GameMgr.h"
#include "ItemPoolManager.h"
#include "ItemSpawner.h"
#include "MonsterSpawner.h"
#include "Player.h"
#include "StatusUi.h"
#include "Structure.h"
#include "TileMap.h"
#include "TopUi.h"
#include "ButtonUi.h"
#include "UIAbilitySelect.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();




	worldView.setSize(size);
	uiView.setSize(size);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	player = AddGo(new Player("Player"));
	auto ui = AddGo(new StatusUi("UI"));
	topUi = AddGo(new TopUi("TopUI"));
	auto buttonUi =	AddGo(new ButtonUi("ButtonUI"));
	buttonUi->Init();
	player->Init();
	ui->Init();
	topUi->Init();
	for (int i = 0; i < 5; i++)
	{
		SetObjPos();
	}

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setCenter(0.f, 0.f);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	RES_TABLE_MGR.LoadScene("Game");
	RES_TABLE_MGR.LoadAnimation();


	auto aep = AddGo(new AttackEntityPoolMgr("AttackEntityPoolMgr"));
	aep->sortingOrder = 10;

	AddGo(new CalculatorMgr("CalculatorMgr"));
	AddGo(new UIAbilitySelect("UIAbilitySelect"));
	AddGo(new GameMgr("GameMgr"));

	abilMgr = AddGo(new AbilityMgr("AbilityMgr"));
	map = AddGo(new TileMap("map"));
	MPMgr = AddGo(new MonsterPoolManager("monsterPoolMgr"));
	itemMPMgr = AddGo(new ItemPoolManager("itemPoolMgr"));
	itemSpawn = AddGo(new ItemSpawner(itemMPMgr));

	monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 400));


	ApplyAddGo();

	for (int i = 0; i < 100; i++)
	{
		SetObjPos();
	}
	ApplyAddGo();
	Scene::Enter();
	
	map->SetOrigin(Origins::MC);
	player->SetScale({ 3.f, 3.f });

	SOUND_MGR.PlayBgm(GET_SOUND("bgm1"), true);
}

void SceneGame::Exit()
{
	for (auto stru : struList)
	{
		ExcludeGo(stru);
		struPool.Return(stru);
	}
	struList.clear();

	SOUND_MGR.StopAllSfx();
	SOUND_MGR.StopBgm();

	RemoveAllGo();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	worldView.setCenter(player->GetPosition());
	if (player->GetIsDead())
	{
		player->Update(dt);
		topUi->Update(dt);
		return;
	}
	Scene::Update(dt);
	if (MPMgr)
	{
		MPMgr->CheckCollisions();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
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
	float posRangeX = -mapFull.x;
	float posRangeY = -mapFull.y ;
	Structure* stru = struPool.Take();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			mapGrid[i][j] = { posRangeX + mapFull.x / 20 * i * 2, posRangeY + mapFull.y / 20 * j * 2 };
		}
	}

	stru->SetKind((Structure::Kinds)Utils::RandomRange(0, 3));
	int posX = Utils::RandomRange(0, 19);
	int posY = Utils::RandomRange(0, 19);

	while (mapGrid[posX][posY] == sf::Vector2f(-1, -1))
	{
		posX = Utils::RandomRange(0, 19);
		posY = Utils::RandomRange(0, 19);
	}
	
	
	stru->SetPosition({ mapGrid[posX][posY].x + posRangeX / 20 * Utils::RandomRange(0.3f, 0.6f), 
		mapGrid[posX][posY].y + posRangeY / 20 * Utils::RandomRange(0.3f, 0.6f) });
	mapGrid[posX][posY] = { -1, -1 };

	struList.push_back(stru);
	AddGo(stru);
}



