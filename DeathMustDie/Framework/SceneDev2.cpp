#include "stdafx.h"
#include "SceneDev2.h"
#include "Monster.h"
#include "AniSkeleton.h"
#include "AniSlime.h"
#include "MonsterPoolManager.h"

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
	ApplyAddGo();

	MPMgr->CreatePool(MonsterTypes::Skeleton, j["Skeleton"], "Skeleton");
	
	aniSlime->SetInfo(j["Slime"]);

	aniSlime->SetOrigin(Origins::BC);
	aniSlime->SetScale({ 3.f, 3.f });
	aniSlime->SetPosition({ 900.f, 900.f });

	aniSlime->Walk();

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

	//sprite ÀÌµ¿
	rectDirection.x = InputMgr::GetAxis(Axis::Horizontal);
	rectDirection.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(rectDirection);
	if (mag > 1.f)
	{
		Utils::Normalize(rectDirection);
	}

	sprite->SetPosition(rectPos + rectDirection * rectSpeed * dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		auto monster = MPMgr->GetMonster("Skeleton");
		monster->SetPosition({ 100.f, 100.f });
		monster->SetScale({ 3.f, 3.f });
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::L))
	{
	}

	Scene::Update(dt);
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