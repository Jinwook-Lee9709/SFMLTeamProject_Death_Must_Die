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

class AniBoss : public Monster
{
public:
	struct BossInfo
	{
		std::string walkAnimId;
		std::string getHitAnimId;
		std::string channelAnimId;
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

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(BossInfo, walkAnimId, getHitAnimId, channelAnimId, deathAnimId,
			walkFrame, getHitFrame, channelFrame, deathFrame,
			damage, speed, hp, ellipseWidth, ellipseHeight);
	};
protected:
	sf::Sprite body;
	Animator Anim;
	std::string textureId;
	BossStatus beforeStatus = BossStatus::None;
	BossStatus currentStatus = BossStatus::Move;

	sf::Vector2f direction;
	float speed = 70.f;
	float attackDelay = 0.f;
	float attackDuration = 3.f;
	int hitCount = 0;

	bool isAttack = false;
	bool isDead = false;

	Player* player;
	BossInfo info;
	Scene* scene;

	sf::FloatRect mapBounds = { 0, 0, 1920, 1080 };

	std::mt19937 rng; // ·£´ý »ý¼º±â
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

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void MoveUpdate(float dt);
	void AttackUpdate(float dt);
	void GetHitUpdate(float dt);
	void ChannelUpdate(float dt);
	void DeathUpdate(float dt);
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void OnDebuffed(DebuffType types) override;

	void Walk(float dt);
	void CheckAttack(float dt);
	void OnHit(float damage);

	sf::Vector2f RandomTPPos();
};

