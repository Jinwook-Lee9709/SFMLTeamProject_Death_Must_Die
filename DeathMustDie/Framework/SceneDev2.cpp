#include "stdafx.h"
#include "SceneDev2.h"
#include "Monster.h"
#include "AniSkeleton.h"
#include "AniSlime.h"
#include "MonsterPoolManager.h"
#include "MonsterSpawner.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
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

void SceneDev2::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev2");
	RES_TABLE_MGR.LoadAnimation();

	MPMgr = AddGo(new MonsterPoolManager());
	sprite = AddGo(new SpriteGo("retreat", "Player"));
	aniSkeleton = new AniSkeleton("AniSkeleton");
	aniSlime = new AniSlime("AniSlime");
	monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 30));
	ApplyAddGo();

	MPMgr->CreatePool(MonsterTypes::Skeleton, j["Skeleton"], "Skeleton");

	aniSlime->SetInfo(j["Slime"]);

	aniSlime->SetOrigin(Origins::BC);
	aniSlime->SetScale({ 3.f, 3.f });
	aniSlime->SetPosition({ 900.f, 900.f });

	Utils::SetOrigin(attackRange, Origins::MC);
	attackRange.setFillColor(sf::Color::White);
	attackRange.setRadius(100.f);

	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	aniSlime->Update(dt);

	sf::Vector2f rectPos = sprite->GetPosition();
	sf::Vector2f skeletonPos = aniSkeleton->GetPosition();

	attackRange.setPosition(skeletonPos);

	//sprite 이동
	rectDirection.x = InputMgr::GetAxis(Axis::Horizontal);
	rectDirection.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(rectDirection);
	if (mag > 1.f)
	{
		Utils::Normalize(rectDirection);
	}

	sprite->SetPosition(rectPos + rectDirection * rectSpeed * dt);

	sf::Vector2f pos = Utils::RandomPointInRect(mapBound);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		for(int i = 0; i < 10; i++)
		{
			auto monster = MPMgr->GetMonster("Skeleton");
			monster->SetPosition(pos);
			monster->SetScale({ 3.f, 3.f });
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::L))
	{
	}

	Scene::Update(dt);

	static float spawnTimer = 0.0f; // 타이머
	const float spawnInterval = 5.0f; // 5초마다 스폰

	spawnTimer += dt;
	if (spawnTimer >= spawnInterval) {
		monsterSpawn->SpawnMonster("Skeleton"); // "Skeleton" 몬스터 스폰
		spawnTimer = 0.0f; // 타이머 초기화
	}
}

void SceneDev2::FixedUpdate(float dt)
{

}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	sprite->Draw(window);
	aniSlime->Draw(window);
	Scene::Draw(window);
}

void SceneDev2::SpawnSkeleton(int count)
{

}