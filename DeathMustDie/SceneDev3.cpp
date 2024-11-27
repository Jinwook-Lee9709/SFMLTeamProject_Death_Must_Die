#include "stdafx.h"
#include "SceneDev3.h"

SceneDev3::SceneDev3() :Scene(SceneIds::Dev3)
{
}

void SceneDev3::Init()
{
	anim.SetTarget(&sprite);
}

void SceneDev3::Release()
{
}

void SceneDev3::Enter()
{
	RES_TABLE_MGR.LoadAnimation();
	anim.Play("crusader_idle");
}

void SceneDev3::Exit()
{
}

void SceneDev3::Update(float dt)
{
	anim.Update(dt);
}

void SceneDev3::LateUpdate(float dt)
{
}

void SceneDev3::FixedUpdate(float dt)
{
}

void SceneDev3::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
