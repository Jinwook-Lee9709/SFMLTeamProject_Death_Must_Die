#include "stdafx.h"
#include "MonsterSpawner.h"
#include "Utils.h"

MonsterSpawner::MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters)
    : poolManager(manager), mapBounds(bounds), rng(std::random_device{}()), maxMonsters(maxMonsters) 
{
    xDist = std::uniform_real_distribution<float>(-100.f, mapBounds.width + 100.f);
    yDist = std::uniform_real_distribution<float>(-100.f, mapBounds.height + 100.f);
}

sf::Vector2f MonsterSpawner::GenerateSpawnPosition() 
{
    float x = xDist(rng);
    float y = yDist(rng);

    // 맵 외곽에서만 스폰하도록 위치 조정
    if (x < 0 || x > mapBounds.width) {
        y = yDist(rng); // x가 맵 외곽이면 y는 랜덤
    }
    else {
        y = (rng() % 2 == 0) ? -100.f : mapBounds.height + 100.f; // y는 상/하 외곽
    }
    return { x, y };
}

void MonsterSpawner::SpawnMonster(const std::string& monsterName) 
{
    if (currentMonsterCount >= maxMonsters) {
        return; // 최대 몬스터 수에 도달했으면 스폰 중단
    }

    Monster* monster = poolManager->GetMonster(monsterName);
    if (monster) {
        monster->SetPosition(GenerateSpawnPosition());
        monster->SetScale({ 3.f, 3.f });
        currentMonsterCount++; // 활성화된 몬스터 수 증가
    }
}

void MonsterSpawner::Init() 
{
    // 초기화 로직
}

void MonsterSpawner::Update(float dt) 
{
    // 몬스터 자동 스폰 로직 (예: 일정 시간마다)
    // SpawnMonster("Skeleton"); // 예시
    SpawnMonster("Skeleton");
}

void MonsterSpawner::OnMonsterDeactivated()
{
    if (currentMonsterCount > 0) 
    {
        currentMonsterCount--;
    }
}
