#pragma once
#include "AttackEntity.h"
class SummonEntity :
    public AttackEntity
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
	
	float timer;
	std::unordered_set<GameObject*> excludedTargets;
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void ChangeInfo(const json& j)override;
	void Activate()override;
};
