#pragma once
#include "AttackEntity.h"

class Player;

class MonsterProjectile :
    public AttackEntity
{
	struct Info {
		std::string AnimId;
		float AnimSize;
		float damage;
		float speed;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, AnimId, AnimSize,
			damage, speed);
	};
protected:
		sf::Sprite sprite;
		Animator animator;
		Info info;

		Player* player;
public:
	MonsterProjectile(const std::string& name = "");
	~MonsterProjectile() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float degree) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Reset() override;
	void Release() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void Activate()override;


};

