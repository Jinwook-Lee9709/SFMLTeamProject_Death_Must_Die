#pragma once
#include "Monster.h"

class AniSlime;

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
	Animator walkAnim;
	Animator attackAnim;
	Animator deathAnim;
	std::string textureId;

	sf::CircleShape attackRange;

	sf::Vector2f direction;
	float speed = 70.f;

	bool isAttack = false;

	SkeletonInfo info;
	AniSlime* aniSlime;
public:
	AniSkeleton(const std::string& name = "");
	~AniSkeleton() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::Vector2f GetPosition() { return position; }
	sf::Sprite GetSprite() const { return body; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void Walk();
	void OnAttack();
	void Die();
};

