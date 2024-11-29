#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include <random>

class MonsterSpawner : public GameObject {
private:
    sf::FloatRect mapBounds; // �� ũ��
    MonsterPoolManager* poolManager; // MonsterPoolManager�� ����
    std::mt19937 rng; // ���� ������
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    int maxMonsters;              // ���� ������ �ִ� ���� ��
    int currentMonsterCount = 0;  // ���� Ȱ��ȭ�� ���� ��

    sf::Vector2f GenerateSpawnPosition();

public:
    MonsterSpawner(MonsterPoolManager* manager, const sf::FloatRect& bounds, int maxMonsters);
    ~MonsterSpawner() = default;

    void SpawnMonster(const std::string& monsterName);
    void Init() override;
    void Update(float dt) override;

    void OnMonsterDeactivated(); // ���� ��Ȱ��ȭ �� ȣ��
};