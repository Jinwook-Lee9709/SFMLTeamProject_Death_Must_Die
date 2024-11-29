#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include <random>

class MonsterSpawner : public GameObject {
private:
    sf::FloatRect mapBounds; // 맵 크기
    MonsterPoolManager* poolManager; // MonsterPoolManager와 연동
    std::mt19937 rng; // 랜덤 생성기
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    int maxMonsters;              // 스폰 가능한 최대 몬스터 수
    int currentMonsterCount = 0;  // 현재 활성화된 몬스터 수

    sf::Vector2f GenerateSpawnPosition();

public:
    MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters);
    ~MonsterSpawner() = default;

    void SpawnMonster(const std::string& monsterName);
    void Init() override;
    void Update(float dt) override;

    void OnMonsterDeactivated(); // 몬스터 비활성화 시 호출
};