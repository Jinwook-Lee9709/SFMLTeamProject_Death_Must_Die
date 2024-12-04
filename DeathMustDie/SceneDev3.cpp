#include "stdafx.h"
#include "SceneDev3.h"
#include "AttackEntityPoolMgr.h"
#include "MonsterPoolManager.h"
#include "AbilityMgr.h"
#include "Player.h"
#include "CalculatorMgr.h"
#include "MonsterPool.h"
#include "MonsterSpawner.h"
#include "UIAbilitySelect.h"
#include "GameMgr.h"

SceneDev3::SceneDev3() :Scene(SceneIds::Dev3)
{
}

void SceneDev3::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	player = AddGo(new Player("Player"));
	worldView.setSize(size);
	uiView.setSize(size);
	Scene::Init();
}

void SceneDev3::Release()
{

}

void SceneDev3::Enter()
{

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setCenter(0.f, 0.f);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	RES_TABLE_MGR.LoadScene("Game");
	RES_TABLE_MGR.LoadAnimation();
	AddGo(new AttackEntityPoolMgr("AttackEntityPoolMgr"));
	AddGo(new CalculatorMgr("CalculatorMgr"));
	AddGo(new GameMgr("GameMgr"));
	AddGo(new AbilityMgr("AbilityMgr"));
	auto obj = AddGo(new UIAbilitySelect("UIAbilitySelect"));
	obj->sortingLayer = SortingLayers::UI;
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
	Scene::LateUpdate(dt);
}

void SceneDev3::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneDev3::Draw(sf::RenderWindow& window)
{
	sf::View saveView = window.getView();
	window.setView(worldView);
	window.draw(sprite2);
	window.setView(saveView);
	
	Scene::Draw(window);
}
