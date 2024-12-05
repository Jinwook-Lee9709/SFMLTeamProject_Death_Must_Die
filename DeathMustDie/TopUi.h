#pragma once

class SceneDev1;
class SceneGame;
class Structure;
class Player;

class TopUi : public GameObject
{
protected:
	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	SceneGame* scene;

	SpriteGo timer;
	TextGo time;
	float minute;
	float sec;

	SpriteGo miniMap;
	SpriteGo miniMapBack;
	SpriteGo markerPlayer;
	std::vector<SpriteGo> markerObj;

	std::list<Structure*> objList;
	Player* player;
public:
	TopUi(const std::string& name = "");
	~TopUi() = default;

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

	void SetTimer();
	void SetTime(float min, float sec);
	void SetMiniMap();
	void SetObjPos();
};

