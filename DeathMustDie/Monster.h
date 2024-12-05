#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:
	float hp = 100.f;

	float tickDuration;          // ���� ���� �ð�
	float tickInterval;      // ƽ ����
	float tickDamage;        // ƽ�� ������
	float tickTimer;         // ƽ Ÿ�̸�

	bool isDebuff = false;

	sf::CircleShape collisionCircle; // ���� �浹ü
	float collisionRadius;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	virtual void SetInfo(const json& j) {}
	virtual void OnHit(float damage) {}
	virtual void OnDebuffed(DebuffType type, float dt) {} // ����� ó��

	void SetCollisionRadius(float radius);
	sf::CircleShape GetCollisionCircle() const;

	bool CheckCollision(const Monster& other) const;
	virtual void OnCollision(Monster* other); // �浹 ó��

	void Draw(sf::RenderWindow& window) override;

	void OnDeath();
};

#define DISTANCE_TO_PLAYER (60.f)
