#pragma once
#include "Monster.h"

enum class Status
{
	None = -1,
	Move,
	Attack,
	GetHit,
	Death,
};

class AniSlime;
class Player;

class AniSkeleton : public Monster
{
public:
	struct SkeletonInfo
	{
		std::string walkAnimId;
		std::string attackAnimId;
		std::string getHitAnimId;
		std::string deathAnimId;
		int walkFrame;
		int attackFrame;
		int getHitFrame;
		int deathFrame;
		float damage;
		float speed;
		float hp;
		float ellipseWidth;
		float ellipseHeight;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SkeletonInfo, walkAnimId, attackAnimId, getHitAnimId, deathAnimId,
			walkFrame, attackFrame, getHitFrame, deathFrame,
			damage, speed, hp, ellipseWidth, ellipseHeight);
	};

protected:
	sf::Sprite body;
	Animator Anim;
	sf::Sprite attackArea;
	std::string textureId;
	Status beforeStatus = Status::None;
	Status currentStatus = Status::Move;

	Player* player;

	sf::Vector2f direction;
	float speed = 70.f;
	float attackDelay = 0.f;
	float attackDuration = 3.f;

	float opacitySpeed = 500.f;
	int opacity = 70;

	sf::Clock clock;
	float animationDuration = 3.f;

	bool isAttack = false;
	bool isDead = false;

	SkeletonInfo info;
	Scene* scene;
	HitBox hitbox2;
public:
	AniSkeleton(const std::string& name = "");
	~AniSkeleton() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetGlobalBounds() const override { return hitbox.rect.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return position; }
	sf::Sprite GetSprite() const { return body; }
	HitBox& GetHitBox2() { return hitbox2; }

	bool GetIsAttack() { return isAttack; }
	bool GetIsDead() { return isDead; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void MoveUpdate(float dt);
	void AttackUpdate(float dt);
	void GetHitUpdate(float dt);
	void DeathUpdate(float dt);
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void OnDebuffed(DebuffType types) override;

	void Walk(float dt);
	void CheckAttack(float dt);
	void OnHit(float damage);
};

