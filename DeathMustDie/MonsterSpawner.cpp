#include "stdafx.h"
#include "MonsterSpawner.h"
#include "Utils.h"
#include "Player.h"

MonsterSpawner::MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters)
    : GameObject("MonsterSpawner"), poolManager(manager), mapBounds(bounds), rng(std::random_device{}()), maxMonsters(maxMonsters)
{
    xDist = std::uniform_real_distribution<float>(-100.f, mapBounds.width + 100.f);
    yDist = std::uniform_real_distribution<float>(-100.f, mapBounds.height + 100.f);
}

sf::Vector2f MonsterSpawner::GenerateSpawnPosition() 
{
    float x = 0;
    float y = 0;
    sf::Vector2f playerPos =  player->GetPosition();
    xDist = std::uniform_real_distribution<float>(playerPos.x - mapBounds.width * 0.5f -100.f, playerPos.x + mapBounds.width + 100.f);
    yDist = std::uniform_real_distribution<float>(playerPos.y - mapBounds.height * 0.5f -100.f, playerPos.y + mapBounds.height + 100.f);
    // 맵 외곽에서만 스폰하도록 위치 조정
    if (Utils::RandomValue() < 0.5f)
    {
        Utils::RandomValue() < 0.5f ? x = playerPos.x - mapBounds.width * 0.5f - 100.f : x = playerPos.x + mapBounds.width * 0.5f + 100.f;
        y = yDist(rng);
    }
    else
    {
        Utils::RandomValue() < 0.5f ? y = playerPos.y - mapBounds.height * 0.5f - 100.f : y = playerPos.y + mapBounds.height * 0.5f + 100.f;
        x = xDist(rng);
    }
    return { x, y };
}

void MonsterSpawner::SpawnMonster(const std::string& monsterName) 
{
    if (currentMonsterCount >= maxMonsters) {
        return; // 최대 몬스터 수에 도달했으면 스폰 중단
    }
    for (int i = 0; i < poolSize; i++)
    {
        Monster* monster = poolManager->GetMonster(monsterName);
        if (monster) {
            monster->SetPosition(GenerateSpawnPosition());
            monster->SetScale({ 3.f, 3.f });
            currentMonsterCount++; // 활성화된 몬스터 수 증가
        }
    }

}

void MonsterSpawner::Init() 
{
    // 초기화 로직
}

void MonsterSpawner::Reset()
{
    player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
    EVENT_HANDLER.AddEvent("OnMonsterDie", [&]() { currentMonsterCount--; });
}

void MonsterSpawner::Update(float dt) 
{
    // 몬스터 자동 스폰 로직 (예: 일정 시간마다)
    // SpawnMonster("Skeleton"); // 예시


    static float spawnTimer = 0.0f; // 타이머
    const float spawnInterval = 1.0f; // 5초마다 스폰

    spawnTimer += dt;
    if (spawnTimer >= spawnInterval) {
        SpawnMonster("Skeleton"); // "Skeleton" 몬스터 스폰
        spawnTimer = 0.0f; // 타이머 초기화
    }
}
