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

    // �� �ܰ������� �����ϵ��� ��ġ ����
    if (x < 0 || x > mapBounds.width) {
        y = yDist(rng); // x�� �� �ܰ��̸� y�� ����
    }
    else {
        y = (rng() % 2 == 0) ? -100.f : mapBounds.height + 100.f; // y�� ��/�� �ܰ�
    }
    return { x, y };
}

void MonsterSpawner::SpawnMonster(const std::string& monsterName) 
{
    if (currentMonsterCount >= maxMonsters) {
        return; // �ִ� ���� ���� ���������� ���� �ߴ�
    }

    Monster* monster = poolManager->GetMonster(monsterName);
    if (monster) {
        monster->SetPosition(GenerateSpawnPosition());
        monster->SetScale({ 3.f, 3.f });
        currentMonsterCount++; // Ȱ��ȭ�� ���� �� ����
    }
}

void MonsterSpawner::Init() 
{
    // �ʱ�ȭ ����
}

void MonsterSpawner::Update(float dt) 
{
    // ���� �ڵ� ���� ���� (��: ���� �ð�����)
    // SpawnMonster("Skeleton"); // ����
    SpawnMonster("Skeleton");
}

void MonsterSpawner::OnMonsterDeactivated()
{
    if (currentMonsterCount > 0) 
    {
        currentMonsterCount--;
    }
}
