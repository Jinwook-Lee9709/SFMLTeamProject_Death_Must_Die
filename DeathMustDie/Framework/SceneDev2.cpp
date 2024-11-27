#include "stdafx.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{	
	Scene::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void SceneDev2::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	Scene::Enter();
	sprite = new SpriteGo("retreat");
	text = new TextGo("Sansation");
	text->SetString("Hi");
	text->SetPosition(sf::Vector2f(400.f, 500.f));
	text->SetFillColor(sf::Color::White);
	text->SetCharacterSize(59);
	text->Reset();
	sprite->Reset();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	sprite->Draw(window);
	text->Draw(window);
	Scene::Draw(window);
}
