#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include <random>

class Player;
class Monster;
class MonsterPoolManager;

class MonsterSpawner : public GameObject 
{
private:
    sf::FloatRect mapBounds; // 맵 크기
    MonsterPoolManager* poolManager; // MonsterPoolManager와 연동
    std::mt19937 rng; // 랜덤 생성기
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    std::uniform_real_distribution<float> randomPosX;
    std::uniform_real_distribution<float> randomPosY;

    int maxMonsters;              // 스폰 가능한 최대 몬스터 수
    int currentMonsterCount = 0;  // 현재 활성화된 몬스터 수
    int poolSize = 10;

    int bossMaxMonsters = 1;
    int bossCurrentMonsterCount = 0;

    int summonMaxMonsters = 10;
    int summonCurrentMonsterCount = 0;

    float worldTimer;

    float spawnTimer = 0.0f;
    float spawnInterval = 5.0f;

    float slimeSpawnTimer = 0.0f;
    float slimeSpawnInterval = 5.0f;

    float bossSpawnTimer = 0.f;

    bool isSlimeSpawn = false;
    bool isBossSpawn = false;
    bool isBossDeSpawn = true;

    std::vector<bool> flags;

    sf::FloatRect rect = { 0, 0, 1920, 1080 };

    sf::Vector2f GenerateSpawnPosition();
    sf::Vector2f RandomBossPosition();

    Player* player;
    Monster* AniMonster;
    MonsterPoolManager* monsterPool;
public:
    MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters);
    ~MonsterSpawner() = default;

    void SpawnMonster(const std::string& monsterName, int poolsize);
    void BossSpawn(const std::string& bossName);
    void SummonMonster(const std::string& monsterName, const GameObject& monster);
    void SummonMonsterTrigger(const GameObject& monster);
    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};
 