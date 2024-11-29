#pragma once
#include "AttackEntity.h"
class TrailEntity : public AttackEntity
{
	struct Info {
		std::string AnimIdStart;
		std::string AnimIdLoop;
		std::string AnimIdEnd;
		float damage;
		float duration;
		float interval;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, AnimIdStart, AnimIdLoop,
			AnimIdEnd, damage, duration, interval);
	};
private:

	Effector effector;
	Info info;

	float timer;
	std::unordered_map<GameObject*, float> excludedTargets;
public:
	TrailEntity(const std::string& name = "");
	~TrailEntity() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void Activate()override;

};

