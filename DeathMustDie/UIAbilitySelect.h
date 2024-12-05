#pragma once
#include "UIPopup.h"
#include "AbilitySelectPanel.h"

class UIAbilitySelect : public UIPopup
{
protected:
	std::vector<AbilitySelectPanel*> panels;

public:
	UIAbilitySelect(const std::string& name = "");
	~UIAbilitySelect() = default;

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

	void SetPanelStatus(std::vector<std::pair<json, UpgradeType>>);
	void EnableUI();
};
