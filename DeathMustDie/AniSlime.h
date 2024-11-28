#pragma once
#include "Monster.h"

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
	Animator walkAnim;
	Animator attackAnim;
	std::string textureId;

	sf::Vector2f direction;
	float speed = 70.f;

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
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j) override;

	void Walk();
	void OnAttack();
};

