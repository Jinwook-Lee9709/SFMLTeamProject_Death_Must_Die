#pragma once
#include "GameObject.h"

class Player;
class MonsterPoolManager;

class Monster : public GameObject
{

protected:
	float hp = 100.f;

	float tickDuration;          // ���� ���� �ð�
	float tickInterval;      // ƽ ����
	float tickDamage;        // ƽ�� ������
	float tickTimer;         // ƽ Ÿ�̸�

	bool isDebuff = false;
	bool isDeath = false;
	bool isSummon = false;

	sf::CircleShape collisionCircle; // ���� �浹ü
	float collisionRadius;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

	Player* player;
	MonsterPoolManager* mpMgr;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	bool IsDeath() { return isDeath; }

	sf::FloatRect GetGlobalBounds() const override { return { 0.f, 0.f, 0.f, 0.f }; }

	virtual void Reset() override;

	virtual void SetInfo(const json& j) {}
	virtual void OnHit(float damage);
	virtual void OnDebuffed(DebuffType type) {} // ����� ó��

	virtual void HandleOverlap(float dt);

	bool GetIsSummon() { return isSummon; }
	bool SetIsSummon(bool summon)
	{
		isSummon = summon;
		return isSummon;
	}

	void SetCollisionRadius(float radius);
	sf::CircleShape GetCollisionCircle() const;

	bool CheckCollision(const Monster& other) const;
	virtual void OnCollision(Monster* other); // �浹 ó��

	void Draw(sf::RenderWindow& window) override;

	void OnDeath();
	void OnSummon();
};

#define DISTANCE_TO_PLAYER (100.f)
#define DISTANCE_TO_OTHER (100.f)
#define PUSH_SPEED (20.f)
