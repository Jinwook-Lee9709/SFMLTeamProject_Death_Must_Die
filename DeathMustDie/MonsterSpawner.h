#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include <random>

class Player;

class MonsterSpawner : public GameObject 
{
private:
    sf::FloatRect mapBounds; // �� ũ��
    MonsterPoolManager* poolManager; // MonsterPoolManager�� ����
    std::mt19937 rng; // ���� ������
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    std::uniform_real_distribution<float> randomPosX;
    std::uniform_real_distribution<float> randomPosY;

    int maxMonsters;              // ���� ������ �ִ� ���� ��
    int currentMonsterCount = 0;  // ���� Ȱ��ȭ�� ���� ��
    int poolSize = 10;

    int bossMaxMonsters = 1;
    int bossCurrentMonsterCount = 0;

    float spawnTimer = 0.0f;
    float spawnInterval = 2.0f;

    float slimeSpawnTimer = 0.0f;
    float slimeSpawnInterval = 2.0f;

    float bossSpawnTimer = 0.f;

    bool isSlimeSpawn = false;
    bool isBossSpawn = false;
    bool isBossDeSpawn = true;

    sf::FloatRect rect = { 0, 0, 1920, 1080 };

    sf::Vector2f GenerateSpawnPosition();
    sf::Vector2f RandomBossPosition();

    Player* player;
public:
    MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters);
    ~MonsterSpawner() = default;

    void SpawnMonster(const std::string& monsterName, int poolsize);
    void BossSpawn(const std::string& bossName);
    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};
 