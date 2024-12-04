#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
public:
protected:
	std::string fontId;
	sf::Text text;
	std::string stringId;

public:
	TextGo();
	TextGo(const std::string& fontId, const std::string& name = "");
	~TextGo() = default;

	const sf::Text& GetText();
	const int& GetFontSize() { return text.getCharacterSize(); }

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFillColor(const sf::Color& color);

	void Set(int size, const sf::Color& color = sf::Color::White);
	void SetString(const std::string& id);
	void SetString(const std::wstring& str);
	void SetStringByString(const std::string& str);
	void SetCharacterSize(int size);
	void SetOutline(int tickness, sf::Color color);
	void SetFont(const std::string& font);
	void SetFont(const sf::Font& font);

	sf::FloatRect GetLocalBounds();
	sf::FloatRect GetGlobalBounds();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnLocalize(Languages lang) override;
};

