#include "stdafx.h"
#include "SceneGame.h"
#include "AbilityMgr.h"
#include "AttackEntityPoolMgr.h"
#include "CalculatorMgr.h"
#include "Player.h"
#include "TileMap.h"
#include "MonsterSpawner.h"
#include "UISkillSelect.h"
#include "GameManager.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	uiView.setSize(size);
	player = AddGo(new Player("Player"));
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setCenter(0.f, 0.f);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	RES_TABLE_MGR.LoadScene("Game");
	RES_TABLE_MGR.LoadAnimation();

	AddGo(new AttackEntityPoolMgr("AttackEntityPoolMgr"));
	AddGo(new CalculatorMgr("CalculatorMgr"));
	AddGo(new GameManager("GameManager"));
	abilMgr = AddGo(new AbilityMgr("AbilityMgr"));
	map = AddGo(new TileMap("map"));
	MPMgr = AddGo(new MonsterPoolManager("monsterPoolMgr"));
	monsterSpawn = AddGo(new MonsterSpawner(MPMgr, mapBound, 30));
	auto obj = AddGo(new UISkillSelect("UISkillSelect"));
	obj->sortingLayer = SortingLayers::UI;
	ApplyAddGo();

	Scene::Enter();
	map->SetOrigin(Origins::MC);
	player->SetScale({ 3.f, 3.f });
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
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
	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		abilMgr->AddAbility("Base Attack");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		abilMgr->AddAbility("Searing Attack");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		abilMgr->AddAbility("Fire Dragon");
	}

	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);

}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}




