#include "stdafx.h"
#include "SceneDev3.h"
#include "FallAttack.h"
#include "AttackEntityPoolMgr.h"
#include "AbilityMgr.h"
#include "Player.h"
#include "AniSkeleton.h"
#include "MonsterPool.h"
#include "MonsterSpawner.h"

SceneDev3::SceneDev3() :Scene(SceneIds::Dev3)
{
}

void SceneDev3::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	player = AddGo(new Player("Player"));
	
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	std::ifstream file1("tables/monster_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
	}
	j = json::parse(file1);
	file1.close();

	Scene::Init();
}

void SceneDev3::Release()
{

}

void SceneDev3::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	RES_TABLE_MGR.LoadAnimation();
	AddGo(new AttackEntityPoolMgr("entityPoolMgr"));
	MPMgr = AddGo(new MonsterPoolManager());
	abilMgr = AddGo(new AbilityMgr("abilityMgr"));
	sprite = AddGo(new SpriteGo("retreat","Rect"));
	monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 30));
	sprite->sortingLayer = SortingLayers::Foreground;
	ApplyAddGo();

	MPMgr->CreatePool(MonsterTypes::Skeleton, j["Skeleton"], "Skeleton");

	Scene::Enter();
	player->SetScale({ 3.f, 3.f });
}

void SceneDev3::Exit()
{
}

void SceneDev3::Update(float dt)
{
	if(InputMgr::GetKeyDown(sf::Keyboard::Num1))
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
	worldView.setCenter(player->GetPosition());

	Scene::Update(dt);
	
	static float spawnTimer = 0.0f; // 타이머
	const float spawnInterval = 5.0f; // 5초마다 스폰

	spawnTimer += dt;
	if (spawnTimer >= spawnInterval) {
		monsterSpawn->SpawnMonster("Skeleton"); // "Skeleton" 몬스터 스폰
		spawnTimer = 0.0f; // 타이머 초기화
	}
}

void SceneDev3::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneDev3::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneDev3::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
