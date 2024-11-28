#include "stdafx.h"
#include "SceneDev2.h"
#include "Monster.h"
#include "AniSkeleton.h"
#include "AniSlime.h"

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
	sprite = new SpriteGo("retreat");
	aniSkeleton = new AniSkeleton("AniSkeleton");
	aniSlime = new AniSlime("AniSlime");
	
	aniSkeleton->SetInfo(j["Skeleton"]);
	aniSlime->SetInfo(j["Slime"]);
	sprite->Reset();
	sprite->SetPosition({ 700.f, 700.f });
	sprite->SetOrigin(Origins::BC);

	aniSkeleton->SetOrigin(Origins::BC);
	aniSkeleton->SetScale({ 3.f, 3.f });
	aniSkeleton->SetPosition({ 500.f, 500.f });

	aniSlime->SetOrigin(Origins::BC);
	aniSlime->SetScale({ 3.f, 3.f });
	aniSlime->SetPosition({ 900.f, 900.f });
	
	aniSkeleton->Walk();
	aniSlime->Walk();
	
	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	aniSkeleton->Update(dt);

	aniSlime->Update(dt);

	sf::Vector2f rectPos = sprite->GetPosition();
	sf::Vector2f skeletonPos = aniSkeleton->GetPosition();

	//sprite 이동
	rectDirection.x = InputMgr::GetAxis(Axis::Horizontal);
	rectDirection.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(rectDirection);
	if (mag > 1.f)
	{
		Utils::Normalize(rectDirection);
	}

	sprite->SetPosition(rectPos + rectDirection * rectSpeed * dt);

	//skeleton이 sprite를 향해 이동
	if (Utils::Distance(skeletonPos, rectPos) > 10)
	{
		direction = Utils::GetNormal(rectPos - skeletonPos);
		aniSkeleton->SetPosition(skeletonPos + direction * speed * dt);
	}

	//skeleton의 x좌표가 sprite의 x좌표보다 클 때 스케일 반전
	if (skeletonPos.x > rectPos.x)
	{
		aniSkeleton->SetScale({ -3.f, 3.f });
	}
	else
	{
		aniSkeleton->SetScale({ 3.f, 3.f });
	}

	Scene::Update(dt);
}

void SceneDev2::FixedUpdate(float dt)
{
	//skeleton과 sprite가 부딪히면 attack애니메이션 출력
	if (Utils::CheckCollision(sprite->GetSprite(), aniSkeleton->GetSprite()))
	{
		isPlaying = true;
		aniSkeleton->OnAttack();
		return;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		aniSkeleton->Die();
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	sprite->Draw(window);
	aniSkeleton->Draw(window);
	aniSlime->Draw(window);
	Scene::Draw(window);
}

void SceneDev2::SpawnSkeleton(int count)
{
	
}