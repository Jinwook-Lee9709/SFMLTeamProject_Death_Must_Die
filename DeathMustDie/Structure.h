#pragma once

class Player;
class ButtonUi;

class Structure : public GameObject
{
public:
	enum class Kinds
	{
		Greed,
		Bookshelf,
		Sanctuary,
		Mineral,
		Coffin,
	};
protected:
	Kinds kind;
	Player* player;

	sf::Sprite body;
	std::string bodySpr = "resource/texture/Sprite/Object/Obelisk_Greed_Base_Spr.png";
	sf::FloatRect collision;
	sf::RectangleShape temp;

	bool isUsed = false;
	bool isInteract;

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

	void SetKind(Kinds kind);
	void ShowInteract();

	bool GetInteract() const { return isInteract; }
	bool GetIsUsed() const { return isUsed; }
};
