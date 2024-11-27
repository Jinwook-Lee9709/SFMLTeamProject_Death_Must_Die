#include "stdafx.h"
#include "SceneDev3.h"
#include "FallAttack.h"

SceneDev3::SceneDev3() :Scene(SceneIds::Dev3)
{
}

void SceneDev3::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	attack = AddGo(new FallAttack());

	std::ifstream file1("tables/skill_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
	}
	j = json::parse(file1);
	file1.close();
	pool = new ObjectPool<FallAttack>(10, j["Meteor Shower"]["AttackEntity"]);

	Scene::Init();
}

void SceneDev3::Release()
{

}

void SceneDev3::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	RES_TABLE_MGR.LoadAnimation();
	auto obj = AddGo(new FallAttack("Test"));
	obj->sortingLayer = SortingLayers::Foreground;
	sprite = AddGo(new SpriteGo("retreat","Rect"));
	sprite->sortingLayer = SortingLayers::Foreground;
	ApplyAddGo();
	Scene::Enter();
}

void SceneDev3::Exit()
{
}

void SceneDev3::Update(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		auto obj = pool->Take();
		AddGo(obj);
		obj->SetPosition(Scene::ScreenToWorld(InputMgr::GetMousePosition()));
		obj->Play();
		attacks.push_back(obj);
	}
	auto it = attacks.begin();
	while (it != attacks.end())
	{
		if (!(*it)->IsActive())
		{
			RemoveGo(*it);
			pool->Return(*it);
			it = attacks.erase(it);
		}
		else
		{
			it++;
		}
	}

	Scene::Update(dt);
}

void SceneDev3::LateUpdate(float dt)
{
}

void SceneDev3::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneDev3::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
