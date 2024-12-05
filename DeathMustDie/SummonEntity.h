#pragma once
#include "AttackEntity.h"

class Player;
class Ability;

class SummonEntity :
    public AttackEntity
{
	struct Info {
		std::string AnimId;
		float AnimSize;
		float damage;
		float speed;
		float attackRange;
		float attackInterval;
		float duration;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, AnimId, AnimSize,
			damage, speed, attackRange, attackInterval, duration);
	};

	enum class Status
	{
		None = -1 ,
		Chase,
		ReturnToPlayer,
		Attack,
	};

protected:
	sf::Sprite sprite;
	Animator animator;
	Info info;

	Ability* abil;

	Player* player;
	GameObject* target;
	Status currentStatus;
	Status beforeStatus;
	float timer;
	float attackTimer;

public:
	SummonEntity(const std::string& name = "");
	~SummonEntity() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Reset() override;
	void Release() override;
	void Update(float dt) override;
	void UpdateChase(float dt);
	void UpdateAttack(float dt);
	void UpdateReturnToPlayer(float dt);
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInfo(const json& j)override;
	void ChangeInfo(const json& j)override;
	void Activate()override;

	void FindTarget();
	void AddAbility(const std::string& skillId);
};

