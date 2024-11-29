#include "stdafx.h"
#include "SceneDev3.h"
#include "FallAttack.h"
#include "AttackEntityPoolMgr.h"
#include "AbilityMgr.h"

SceneDev3::SceneDev3() :Scene(SceneIds::Dev3)
{
}

void SceneDev3::Init()
{
	sf::Vector2f size = 0.7f * FRAMEWORK.GetWindowSizeF();
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
	RES_TABLE_MGR.LoadAnimation();
	AddGo(new AttackEntityPoolMgr("entityPoolMgr"));
	abilMgr = AddGo(new AbilityMgr("abilityMgr"));
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
	sf::Vector2f center = worldView.getCenter();
	center.x += InputMgr::GetAxis(Axis::Horizontal) * dt * 200;
	center.y += InputMgr::GetAxis(Axis::Vertical) * dt* 200;
	worldView.setCenter(center);
	Scene::Update(dt);
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
