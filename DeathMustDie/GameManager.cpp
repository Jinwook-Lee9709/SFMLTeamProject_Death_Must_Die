#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(const std::string& name)
	: GameObject(name)
{
}
void GameManager::Init()
{
}

void GameManager::Release()
{
}

void GameManager::Reset()
{
	skillSelectUi = (UISkillSelect*)SCENE_MGR.GetCurrentScene()->FindGo("UISkillSelect");
}

void GameManager::Update(float dt)
{
	switch (currentStatus)
	{
		case Status::IDLE:
		{
			UpdateIdle(dt);
			break;
		}
		case Status::SELECT_SKILL:
		{
			UpdateSelectSkill(dt);
			break;
		}
	}
}

void GameManager::UpdateIdle(float dt)
{

}

void GameManager::UpdateSelectSkill(float dt)
{
	if (beforeStatus != Status::None)
	{

	}
}

void GameManager::Draw(sf::RenderWindow& window)
{
}
