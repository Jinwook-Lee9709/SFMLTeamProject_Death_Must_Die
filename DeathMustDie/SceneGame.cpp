#include "stdafx.h"
#include "SceneGame.h"
#include "AbilityMgr.h"
#include "AttackEntityPoolMgr.h"
#include "MonsterSpawner.h"
#include "CalculatorMgr.h"
#include "Player.h"
#include "TileMap.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
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
	AddGo(new CalculatorMgr("CalculatorMgr"));
	abilMgr = AddGo(new AbilityMgr("AbilityMgr"));
	MPMgr = AddGo(new MonsterPoolManager("monsterPoolMgr"));
	//monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 30));
	ApplyAddGo();

	std::ifstream file1("tables/monster_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
	}
	json j = json::parse(file1);
	MPMgr->CreatePool(MonsterTypes::Skeleton, j["Skeleton"], "Skeleton");

	Scene::Enter();
	map->SetOrigin(Origins::MC);
	player->SetScale({ 3.f, 3.f });
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		abilMgr->AddAbility("Meteor Shower");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		abilMgr->AddAbility("Breath of Fire");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		abilMgr->AddAbility("Trail of Fire");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		abilMgr->AddAbility("Base Attack");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F))
	{
		auto monster = MPMgr->GetMonster("Skeleton");
		monster->SetPosition({ 100.f, 100.f });
		monster->SetScale({ 3.f, 3.f });
	}

	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);

	//static float spawnTimer = 0.0f; // 타이머
	//const float spawnInterval = 5.0f; // 5초마다 스폰

	//spawnTimer += dt;
	//if (spawnTimer >= spawnInterval) {
	//	monsterSpawn->SpawnMonster("Skeleton"); // "Skeleton" 몬스터 스폰
	//	spawnTimer = 0.0f; // 타이머 초기화
	//}
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}




