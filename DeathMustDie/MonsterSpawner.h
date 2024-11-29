#pragma once
#include "GameObject.h"

class AniSkeleton;
class MonsterPoolManager;

class MonsterSpawner : public GameObject
{
private:
	AniSkeleton* skeleton;
	MonsterPoolManager* MPMgr;
	json j;

public:
	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void SkeletonSqawn(int count);
};

