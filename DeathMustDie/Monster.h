#pragma once
#include "GameObject.h"

class Monster : public GameObject
{

protected:
	float hp = 100.f;

	float tickDuration;          // 남은 지속 시간
	float tickInterval;      // 틱 간격
	float tickDamage;        // 틱당 데미지
	float tickTimer;         // 틱 타이머

	bool isDebuff = false;
	bool isDeath = false;

	sf::CircleShape collisionCircle; // 원형 충돌체
	float collisionRadius;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPBarFrame;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	bool IsDeath() { return isDeath; }

	virtual void SetInfo(const json& j) {}
	virtual void OnHit(float damage) {}
	virtual void OnDebuffed(DebuffType type) {} // 디버프 처리

	void SetCollisionRadius(float radius);
	sf::CircleShape GetCollisionCircle() const;

	bool CheckCollision(const Monster& other) const;
	virtual void OnCollision(Monster* other); // 충돌 처리

	void Draw(sf::RenderWindow& window) override;

	void OnDeath();
};

#define DISTANCE_TO_PLAYER (60.f)
