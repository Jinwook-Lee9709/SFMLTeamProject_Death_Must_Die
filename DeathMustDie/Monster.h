#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId;
	Animator anim;

	sf::Vector2f direction;

	sf::RectangleShape player;

	float speed = 70.f;

public:
	Monster(const std::string& texId, const std::string& name = "");
	~Monster() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& size) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	HitBox& GetHitBox() override
	{
		return hitbox;
	}

	sf::Sprite GetSprite() const { return body; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnAttack();
	void OnDamage();
};

