#pragma once
#include "Item.h"

class Gem : public Item
{
public:
	struct GemInfo
	{
		std::string textureId;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(GemInfo, textureId);
	};

protected:
	sf::Sprite body;

	json j;

	GemInfo info;
	
public:
	Gem(const std::string& name = "");
	~Gem() = default;
	
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& size) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	void SetInfo(const json& j) override;

	void Reset();
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

