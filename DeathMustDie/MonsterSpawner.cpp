#include "stdafx.h"
#include "MonsterSpawner.h"
#include "Utils.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterPoolManager.h"

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
	sf::Vector2f playerPos = player->GetPosition();
	xDist = std::uniform_real_distribution<float>(playerPos.x - mapBounds.width * 0.5f - 100.f, playerPos.x + mapBounds.width + 100.f);
	yDist = std::uniform_real_distribution<float>(playerPos.y - mapBounds.height * 0.5f - 100.f, playerPos.y + mapBounds.height + 100.f);

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

sf::Vector2f MonsterSpawner::RandomBossPosition()
{
	float x = 0;
	float y = 0;
	sf::Vector2f playerPos = player->GetPosition();
	
	randomPosX = std::uniform_real_distribution<float>(playerPos.x - mapBounds.width * 0.5f, playerPos.x + mapBounds.width * 0.5f);
	randomPosY = std::uniform_real_distribution<float>(playerPos.y - mapBounds.height * 0.5f, playerPos.y + mapBounds.height * 0.5f);

	x = randomPosX(rng);
	y = randomPosY(rng);

	sf::Vector2f randomPos = { x, y };

	return randomPos;

}

void MonsterSpawner::SpawnMonster(const std::string& monsterName, int poolsize)
{
	poolSize = poolsize;

	if (currentMonsterCount >= maxMonsters)
	{
		return;
	}
	for (int i = 0; i < poolSize; i++)
	{
		Monster* monster = poolManager->GetMonster(monsterName);
		if (monster)
		{
			monster->SetPosition(GenerateSpawnPosition());
			monster->SetScale({ 3.f, 3.f });
			currentMonsterCount++;
		}
	}
}

void MonsterSpawner::BossSpawn(const std::string& bossName)
{
	if (bossCurrentMonsterCount >= bossMaxMonsters)
	{
		return;
	}
	for (int i = 0; i < 1; i++)
	{
		Monster* bossMonster = poolManager->GetMonster(bossName);
		if (bossMonster)
		{
			bossMonster->SetPosition(RandomBossPosition());
			bossMonster->SetScale({ 3.f, 3.f });
			bossCurrentMonsterCount++;
		}
	}
}

void MonsterSpawner::SummonMonster(const std::string& monsterName, const GameObject& monster)
{
	if (summonCurrentMonsterCount < 0.f)
	{
		summonCurrentMonsterCount = 0.f;
	}

	if (summonCurrentMonsterCount >= summonMaxMonsters)
	{
		return;
	}
	for (int i = 0; i < summonMaxMonsters; i++)
	{
		Monster* summonMonster = poolManager->GetMonster(monsterName);
		if (summonMonster)
		{
			summonMonster->SetPosition(RandomBossPosition());
			summonMonster->SetScale({ 3.f, 3.f });
			summonCurrentMonsterCount++;
		}
	}

	std::cout << summonCurrentMonsterCount << std::endl;
}

void MonsterSpawner::SummonMonsterTrigger(const GameObject& monster)
{
	SummonMonster("Skeleton", monster);
}

void MonsterSpawner::Init()
{

}

void MonsterSpawner::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
	EVENT_HANDLER.AddEvent("OnMonsterDie", [&]() { currentMonsterCount--; });
	EVENT_HANDLER.AddEvent("OnSummonMonsterDie", [&]() {summonCurrentMonsterCount--; });
	std::function<void(const GameObject&)> func = std::bind(&MonsterSpawner::SummonMonsterTrigger, this, std::placeholders::_1);

	EVENT_HANDLER.AddEventGo("SummonSkeleton", func);

	flags = { false, false, false };
	worldTimer = 0;
}

void MonsterSpawner::Update(float dt)
{
	worldTimer += dt;

	if (worldTimer > 60.f && flags[0] == false)
	{
		SpawnMonster("Skeleton", 150);
		flags[0] = true;
	}

	if (worldTimer > 120.f && flags[1] == false)
	{
		SpawnMonster("Slime", 150);
		flags[1] = true;
	}

	if (worldTimer > 160.f && flags[2] == false)
	{
		EVENT_HANDLER.InvokeEvent("OnBossSummon");
		BossSpawn("Boss");
		flags[2] = true;
	}

	spawnTimer += dt;
	slimeSpawnTimer += dt;

	bossSpawnTimer += dt;

	if (spawnTimer >= spawnInterval)
	{
		SpawnMonster("Skeleton", 5);
		spawnTimer = 0.0f;
	}

	if (slimeSpawnTimer >= 90.f)
	{
		isSlimeSpawn = true;
		slimeSpawnTimer = 0.0f;
	}

	if (isSlimeSpawn && slimeSpawnTimer >= slimeSpawnInterval)
	{
		SpawnMonster("Slime", 5);
		slimeSpawnTimer = 0.0f;
	}

	//if (bossSpawnTimer >= 1.f)
	//{
	//	BossSpawn("Boss");
	//	isBossSpawn = true;
	//	bossSpawnTimer = 0.f;
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::L))
	{
		BossSpawn("Boss");
		bossSpawnTimer = 0.f;
		EVENT_HANDLER.InvokeEvent("OnBossSummon");
	}
}
