#pragma once

class TileMap2 : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId = "resource/texture/TerrainWilderness_Spr_01.png";
	sf::Texture* texture = nullptr;
	sf::Transform transform;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

	sf::Sprite temp;
public:
	TileMap2(const std::string& name = "");
	~TileMap2() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
	sf::FloatRect GetMoveableBounds() const;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void SetPoint(sf::Transformable& obj, const sf::Vector2i& pos);
	void UpdateTransform();
};
