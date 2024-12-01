#pragma once
#include "stdafx.h"
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;
	std::string playername;
public:
	SpriteGo(const std::string & texId = "", const std::string & name = "");
	~SpriteGo() = default;

	void SetTextureId(const std::string& id) { textureId = id; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void FlipX(bool flag) override;
    void FlipY(bool flag) override;

	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
	std::string GetTexId() const { return textureId; }
	sf::Sprite GetSprite() const { return sprite; }

	void SetFillColor(const sf::Color& color);
	void ChangeTexture(const std::string& texId);

	virtual sf::Vector2f GetSize();
};

