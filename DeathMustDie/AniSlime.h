#pragma once
#include "Monster.h"
#include "Timer.h"

enum class SlimeStatus
{
	None = -1,
	Move,
	Attack,
	GetHit,
	Death,
};

class Player;

class AniSlime : public Monster
{
public:
	struct SlimeInfo
	{
		std::string walkAnimId;
		std::string attackAnimId;
		std::string deathAnimId;
		int walkFrame;
		int attackFrame;
		int deathFrame;
		float damage;
		float speed;
		float hp;
		float ellipseWidth;
		float ellipseHeight;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SlimeInfo, walkAnimId, attackAnimId, deathAnimId,
			walkFrame, attackFrame, deathFrame,
			damage, speed, hp, ellipseWidth, ellipseHeight);
	};

protected:
	sf::Sprite body;
	sf::Sprite attackArea;
	Animator Anim;
	std::string textureId;

	SlimeStatus beforeStatus = SlimeStatus::None;
	SlimeStatus currentStatus = SlimeStatus::Move;

	HitBox hitbox2;

	sf::Vector2f direction;
	float speed = 70.f;
	float hitTime = 0.f;
	float hitDuration = 1.f;
	float attackDelay = 0.f;
	float attackDuration = 3.f;

	Timer atkTimer;
	int opacity = 70;
	float opacitySpeed = 500.f;

	bool isGetHit = false;
	bool isAttack = false;
	bool isDead = false;

	SlimeInfo info;
public:
	AniSlime(const std::string& name = "");
	~AniSlime() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::Vector2f GetPosition() { return position; }

	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void MoveUpdate(float dt);
	void AttackUpdate(float dt);
	void GetHitUpdate(float dt);
	void DeathUpdate(float dt);
	void FixedUpdate(float dt)override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void Walk(float dt);
	void OnAttack();
	void OnHit(float damage);
};

