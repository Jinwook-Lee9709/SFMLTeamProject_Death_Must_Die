#include "stdafx.h"
#include "UIAbilitySelect.h"

UIAbilitySelect::UIAbilitySelect(const std::string& name)
	: UIPopup(name)
{
}

void UIAbilitySelect::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UIAbilitySelect::SetRotation(float angle)
{
	rotation = angle;
}

void UIAbilitySelect::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UIAbilitySelect::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UIAbilitySelect::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UIAbilitySelect::Init()
{
}

void UIAbilitySelect::Release()
{
	panels.clear();
}

void UIAbilitySelect::Reset()
{
	sf::Vector2f initPos = { 300.f, 100.f };
	for (int i = 0; i < 3; i++)
	{
		AbilitySelectPanel* panel = new AbilitySelectPanel("panel" + std::to_string(i), i);
		panel->Reset();
		panel->SetPosition(initPos);
		panel->SetScale({ 1.f, 1.f });
		initPos.x += 500.f;
		panels.push_back(panel);
	}
}

void UIAbilitySelect::Update(float dt)
{
	for (auto& panel : panels)
	{
		panel->Update(dt);
	}
}

void UIAbilitySelect::Draw(sf::RenderWindow& window)
{
	for (auto& panel : panels)
	{
		panel->Draw(window);
	}
}

void UIAbilitySelect::SetPanelStatus(std::vector<std::pair<json, UpgradeType>> abilInfo)
{
	int i = 0;
	auto it = panels.begin();
	for (auto& pair : abilInfo)
	{
		(*it)->UpdateDisplay(pair.first, pair.second);
		it++;
		i++;
	}
	for (int j = i; j < panels.size(); j++)
	{
		panels[j]->SetActive(false);
	}
}

void UIAbilitySelect::EnableUI()
{
	for (auto& panel : panels)
	{
		panel->Display();
	}
}
