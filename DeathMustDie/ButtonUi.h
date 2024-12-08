#pragma once

class ButtonUi : public GameObject
{
protected:
	SpriteGo body;
	TextGo buttonName;

	std::string btnName;
	int trans;
	bool buttonVisible;
public:
	ButtonUi(const std::string& name = "");
	~ButtonUi() = default;

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

	void SetButton(const std::string& btnName);
	void SetButtonName(const std::wstring& btnName);
	void SetButtonVisible(bool tf) { buttonVisible = tf; }
};
