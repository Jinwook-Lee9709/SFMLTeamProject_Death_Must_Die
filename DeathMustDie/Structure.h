#pragma once

class Structure : public GameObject
{
public:
	enum class Kinds
	{
		Back,
		Obstacle,
		Interactive,
	};
protected:
	Kinds kind;

	sf::Sprite body;
	sf::FloatRect collision;
	sf::RectangleShape temp;

	bool isUsed;

public:
	Structure(const std::string& name = "");
	~Structure() = default;

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
