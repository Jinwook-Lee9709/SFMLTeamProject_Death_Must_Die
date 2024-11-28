#include "stdafx.h"
#include "SceneDev1.h"
#include "Player.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	player = AddGo(new Player("Knight"));

	Scene::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size * 0.35f);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	
}

void SceneDev1::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	Scene::Enter();
	sprite = new SpriteGo("background");
	sprite->Reset();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 

	Scene::Update(dt);

	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	
	//text->Draw(window);
	sprite->Draw(window);
	Scene::Draw(window);
	
}
