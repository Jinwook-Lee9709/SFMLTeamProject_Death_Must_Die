#pragma once
struct SpriteInfo
{
	sf::Vector2f position;
	sf::Vector2f scale;
	Origins origin;
};
struct TextInfo
{
	sf::Vector2f position;
	sf::Vector2f scale;
	Origins origin;
	int chracterSize;
	std::string font;
};


class SkillSelectPanel : public GameObject
{
public:
	
protected:
	Animator animator;
	std::unordered_map<std::string, sf::Sprite*> sprites;
	std::unordered_map<std::string, TextGo> texts;
	//sf::Sprite Panel;
	//sf::Sprite rarityFrame;
	//TextGo skillName;
	//TextGo level;
	//TextGo rarityText;
	//TextGo skillType;
	//TextGo instruct;
	std::vector<std::pair<TextGo, TextGo>> skillValue;
	sf::RenderTexture* texBuf;
	sf::Sprite canvas;
	float opacity;
public:
	SkillSelectPanel(const std::string& name = "");
	~SkillSelectPanel() = default;

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

	void SetComponent();
};


void to_json(json& j, const SpriteInfo& m);
void from_json(const json& j, SpriteInfo& m);
void to_json(json& j, const TextInfo& m);
void from_json(const json& j, TextInfo& m);

