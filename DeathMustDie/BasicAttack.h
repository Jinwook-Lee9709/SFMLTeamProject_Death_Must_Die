#pragma once
#include "AttackEntity.h"
class BasicAttack : public AttackEntity
{
	struct Info {
		float damage;
		float rangeDegree;
		float radius;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info,
			damage, rangeDegree, radius);
	};

protected:
	Info info;

	std::unordered_set<GameObject*> excludedTargets;
public:
	BasicAttack(const std::string& name = "");
	~BasicAttack() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float degree) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void Activate()override;


};

