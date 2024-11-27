#include "stdafx.h"
#include "SceneDev2.h"
#include "Monster.h"

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

	anim.SetTarget(&spr);
}

void SceneDev2::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev2");
	Scene::Enter();
	sprite = new SpriteGo("retreat");
	text = new TextGo("Sansation");
	skeleton = new Monster("Skeleton");
	slime = new Monster("Slime");
	text->SetString("Hi");
	text->SetPosition(sf::Vector2f(400.f, 500.f));
	text->SetFillColor(sf::Color::White);
	text->SetCharacterSize(59);
	text->Reset();

	sprite->Reset();
	skeleton->Reset();

	slime->Reset();
	slime->SetPosition({ 300.f, 300.f });

	spr.setScale({ 2.f, 2.f });
	spr.setPosition({ 100.f, 0.f });

	RES_TABLE_MGR.LoadAnimation();
	anim.Play("skeleton_walk");
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
	skeleton->Update(dt);
	slime->Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		anim.Play("skeleton_attack");
	}

	anim.Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	sprite->Draw(window);
	text->Draw(window);
	skeleton->Draw(window);
	slime->Draw(window);
	window.draw(spr);
	Scene::Draw(window);
}
