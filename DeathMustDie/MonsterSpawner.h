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

    int maxMonsters;              // ���� ������ �ִ� ���� ��
    int currentMonsterCount = 0;  // ���� Ȱ��ȭ�� ���� ��
    int poolSize = 10;

    float spawnTimer = 0.0f;
    float spawnInterval = 2.0f;

    float slimeSpawnTimer = 0.0f;
    float slimeSpawnInterval = 2.0f;

    bool isSlimeSpawn = false;

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
 