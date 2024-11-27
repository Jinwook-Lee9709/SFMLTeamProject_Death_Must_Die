#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	Scene::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void SceneDev1::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	Scene::Enter();
	sprite = new SpriteGo("retreat");
	text = new TextGo("Sansation");
	text->SetString("ContinueText");
	text->SetPosition(sf::Vector2f(400.f, 500.f));
	text->SetFillColor(sf::Color::White);
	text->SetCharacterSize(59);
	text->Reset();
	sprite->SetFillColor(sf::Color::White);
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
	sprite->Draw(window);
	text->Draw(window);
	Scene::Draw(window);
}
