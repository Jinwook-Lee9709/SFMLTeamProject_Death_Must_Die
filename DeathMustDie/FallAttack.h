#pragma once
#include "AttackEntity.h"

#pragma once

class FallAttack : public AttackEntity
{
protected:
	float damage;
	float duration;
	sf::Vector2f ellipseRadius;
	sf::CircleShape circle;
public:
	FallAttack(const std::string& name = "");
	~FallAttack() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
