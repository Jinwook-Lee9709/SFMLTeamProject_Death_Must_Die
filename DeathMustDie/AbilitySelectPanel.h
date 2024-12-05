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

class Scene;

class AbilitySelectPanel : public GameObject
{
public:
	
protected:
	int panelNum;

	Animator animator;
	Animator hoverAnimator;
	Animator effectAnimator;
	std::unordered_map<std::string, sf::Sprite*> sprites;
	std::unordered_map<std::string, TextGo> texts;
	std::list<std::pair<TextGo, TextGo>>  valueTexts;

	int valueCharacterSize;
	std::string fontId;

	std::vector<std::pair<TextGo, TextGo>> skillValue;
	sf::RenderTexture* texBuf;
	sf::Sprite canvas;
	float opacity;
	bool isHover = false;
	bool selected = false;

	sf::Vector2f selectEffectPos;

	Scene* currentScene;
	//sf::Sprite panel;
	//sf::Sprite rarityFrame;
	//TextGo skillName;
	//TextGo level;
	//TextGo rarityText;
	//TextGo skillType;
	//TextGo instruct;
	json setting;
public:
	AbilitySelectPanel(const std::string& name = "", int num = 0);
	~AbilitySelectPanel() = default;

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
	void UpdateDisplay(const json& skillInfo, UpgradeType type);
	void Display();
	void CreateValueText(int count);
	void SetValueText(const json& valueText);

	void TurnOffPanel(int num);

	std::string AbilityTypeToString(const AbilityType& type);
	std::string GradeToString(const AbilityGrade& grade);
};


void to_json(json& j, const SpriteInfo& m);
void from_json(const json& j, SpriteInfo& m);
void to_json(json& j, const TextInfo& m);
void from_json(const json& j, TextInfo& m);

