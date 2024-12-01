#pragma once
#include "AttackEntity.h"

class WedgeAttack : public AttackEntity
{
	struct Info {
		std::string AnimId;
		float AnimSize;
		float damage;
		float rangeDegree;
		float radius;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, AnimId, AnimSize,
			 damage, rangeDegree, radius);
	};

protected:
	sf::Sprite sprite;
	Animator animator;
	Info info;

	std::unordered_set<GameObject*> excludedTargets;
public:
	WedgeAttack(const std::string& name = "");
	~WedgeAttack() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float degree) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void ChangeInfo(const json& j)override;
	void Activate()override;


};

