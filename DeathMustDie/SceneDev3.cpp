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
	Scene::Init();
}

void SceneDev3::Release()
{

}

void SceneDev3::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
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
