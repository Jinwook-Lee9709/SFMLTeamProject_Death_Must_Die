#pragma once
#include "Monster.h"
#include <random>

enum class BossStatus
{
	None = -1,
	Move,
	Attack,
	GetHit,
	Channel,
	Death,
};

class Player;
class AttackEntityPoolMgr;

class AniBoss : public Monster
{
public:
	struct BossInfo
	{
		std::string walkAnimId;
		std::string getHitAnimId;
		std::string channelAnimId;
		std::string channelParticleAnimId;
		std::string deathAnimId;
		int walkFrame;
		int getHitFrame;
		int channelFrame;
		int deathFrame;
		float damage;
		float speed;
		float hp;
		float ellipseWidth;
		float ellipseHeight;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(BossInfo, walkAnimId, getHitAnimId, channelAnimId, channelParticleAnimId, deathAnimId,
			walkFrame, getHitFrame, channelFrame, deathFrame,
			damage, speed, hp, ellipseWidth, ellipseHeight);
	};
protected:
	sf::Sprite body;
	sf::Sprite particleBody;
	Animator Anim;
	Animator ParticleAnim;
	std::string textureId;
	BossStatus beforeStatus = BossStatus::None;
	BossStatus currentStatus = BossStatus::Move;

	sf::CircleShape circle;

	sf::Vector2f direction;
	float speed = 20.f;
	float attackDelayTimer = 0.f;
	float attackDelay = 0.f;
	float attackDuration = 6.f;
	int hitCount = 0;

	sf::Vector2f randomBossPos;

	bool isAttack = false;
	bool isDead = false;
	bool isAbilityUsed = false;
	bool isFire = false;
	bool isArrival = false;

	BossInfo info;
	Scene* scene;

	AttackEntityPoolMgr* poolMgr;
	sf::FloatRect mapBounds = { 0, 0, 1920, 1080 };

	std::mt19937 rng; // ���� ������
	std::uniform_real_distribution<float> randomPosX;
	std::uniform_real_distribution<float> randomPosY;
public:
	AniBoss(const std::string& name = "");
	~AniBoss() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetGlobalBound() { return hitbox.rect.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return position; }
	sf::Sprite GetSprite() const { return body; }

	bool GetIsAttack() { return isAttack; }
	bool GetIsDead() { return isDead; }
	bool GetIsSummon() { return isSummon; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void MoveUpdate(float dt);
	void AttackUpdate(float dt);
	void GetHitUpdate(float dt);
	void ChannelUpdate(float dt);
	void DeathUpdate(float dt);
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void OnDebuffed(DebuffType types) override;

	void Walk(float dt);
	void CheckAttack(float dt);
	void OnHit(float damage);
	void FireProjectile();

	sf::Vector2f RandomTPPos();
	sf::Vector2f RandomPointInCircle();
	void SetRandomPointInCircle();
};

#define DISTANCE_TO_PLAYER_BOSS (400.f)
