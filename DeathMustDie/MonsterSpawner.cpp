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
    // �� �ܰ������� �����ϵ��� ��ġ ����
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
    if (currentMonsterCount >= maxMonsters) 
    {
        return; // �ִ� ���� ���� ���������� ���� �ߴ�
    }
    for (int i = 0; i < poolSize; i++)
    {
        Monster* monster = poolManager->GetMonster(monsterName);
        if (monster) {
            monster->SetPosition(GenerateSpawnPosition());
            monster->SetScale({ 3.f, 3.f });
            currentMonsterCount++; // Ȱ��ȭ�� ���� �� ����
        }
    }

}

void MonsterSpawner::Init() 
{
    // �ʱ�ȭ ����
}

void MonsterSpawner::Reset()
{
    player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
    EVENT_HANDLER.AddEvent("OnMonsterDie", [&]() { currentMonsterCount--; });
}

void MonsterSpawner::Update(float dt) 
{
    // ���� �ڵ� ���� ���� (��: ���� �ð�����)
    // SpawnMonster("Skeleton"); // ����


    static float spawnTimer = 0.0f; // Ÿ�̸�
    const float spawnInterval = 1.0f; // 5�ʸ��� ����

    spawnTimer += dt;
    if (spawnTimer >= spawnInterval) {
        SpawnMonster("Skeleton"); // "Skeleton" ���� ����
        spawnTimer = 0.0f; // Ÿ�̸� �ʱ�ȭ
    }
}
