#pragma once
#include "AttackEntity.h"

class FallAttack : public AttackEntity
{
	struct Info {
		std::string fallAnimId;
		std::string impactAnimId;
		int impactFrame;
		float fallAnimSize;
		float damage;
		float speed;
		float ellipseWidth;
		float ellipseHeight;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, fallAnimId, impactAnimId,
			impactFrame, fallAnimSize, damage, speed, ellipseWidth, ellipseHeight);
	};

protected:
	sf::Sprite fallSprite;
	sf::Sprite impactSprite;
	Animator fallAnimator;
	Animator impactAnimator;
	bool isImpacted;
	Info info;

public:
	FallAttack(const std::string& name = "");
	~FallAttack() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void Activate()override;
	void StartImpactAnim();
};
