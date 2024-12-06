#pragma once
#include "GameObject.h"

class Button : public GameObject
{
protected:
	TextGo text;
public:
	Button(const std::string& name = "");
	~Button() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetFont(std::string fontId);
	void SetString(std::string stringId);
	void SetCharacterSize(int size);
};

