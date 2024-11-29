#include "stdafx.h"
#include "MonsterSpawner.h"
#include "AniSkeleton.h"
#include "MonsterPoolManager.h"

void MonsterSpawner::Init()
{

}

void MonsterSpawner::Release()
{

}

void MonsterSpawner::Reset()
{

}

void MonsterSpawner::Update(float dt)
{

}

void MonsterSpawner::FixedUpdate(float dt)
{

}

void MonsterSpawner::Draw(sf::RenderWindow& window)
{

}

void MonsterSpawner::SkeletonSqawn(int count)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		auto monster = MPMgr->GetMonster("Skeleton");
		monster->SetPosition({ 100.f, 100.f });
	}
}
