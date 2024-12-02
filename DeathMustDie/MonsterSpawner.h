#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include <random>

class Player;

class MonsterSpawner : public GameObject {
private:
    sf::FloatRect mapBounds; // 맵 크기
    MonsterPoolManager* poolManager; // MonsterPoolManager와 연동
    std::mt19937 rng; // 랜덤 생성기
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    int maxMonsters;              // 스폰 가능한 최대 몬스터 수
    int currentMonsterCount = 0;  // 현재 활성화된 몬스터 수
    int poolSize = 10;


    sf::Vector2f GenerateSpawnPosition();

    Player* player;
public:
    MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters);
    ~MonsterSpawner() = default;

    void SpawnMonster(const std::string& monsterName);
    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};
 