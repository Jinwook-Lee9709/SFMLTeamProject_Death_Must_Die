#pragma once
#include "Player.h"
#include "ButtonUi.h"

class SceneGame;

class StatusUi : public GameObject
{
protected:
	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	SceneGame* scene;
	Stat stat;

	SpriteGo boonsBtn;
	SpriteGo boonsBtnGlow;
	int boonTrans = 0;

	SpriteGo inventoryBtn;
	SpriteGo inventoryBtnGlow;
	int inventoryTrans = 0;

	SpriteGo expFrame;
	SpriteGo expUnderFrame;
	SpriteGo exp;

	SpriteGo portraitFrame;
	SpriteGo portrait;
	SpriteGo level;
	TextGo levelNum;

	SpriteGo hpFrame;
	SpriteGo hp;
	SpriteGo hpTrace;
	TextGo hpText;

	std::vector<SpriteGo> staminaFrame;
	std::vector<SpriteGo> stamina;
	SpriteGo staminaEnd;

	std::vector<ButtonUi> btns;
	float visibleTime;

	Player* player;

public:
	StatusUi(const std::string& name = "");
	~StatusUi() = default;

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

	void SetBoons();
	void SetInventory();
	void SetExpFrame();
	void SetPortrait();
	void SetHpFrame();
	void SetStaminaFrame();
	void SetBtns();

	void cursorBoons(float dt);
	void cursorInventory(float dt);

	void UpdateDashCount(int dashCharge);
	void UpdateHp(float changeHp, float damage = 0);
	void UpdateTrace();
	void UpdateExp(float exp, int level);

	void isInteract(bool interact);

};
