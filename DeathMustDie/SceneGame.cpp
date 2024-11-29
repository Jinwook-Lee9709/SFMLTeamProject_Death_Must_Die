#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "FallAttack.h"
#include "AttackEntityPoolMgr.h"
#include "AbilityMgr.h"
#include "Player.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	RES_TABLE_MGR.LoadScene("Dev1");
	RES_TABLE_MGR.LoadAnimation();
	AddGo(new AttackEntityPoolMgr("entityPoolMgr"));
	abilMgr = AddGo(new AbilityMgr("abilityMgr"));

	ApplyAddGo();

	Scene::Enter();
}

void SceneGame::Exit()
{
	
	Scene::Exit();
}

void SceneGame::Reset()
{

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

}

void SceneGame::Update(float dt)
{
	

}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}




