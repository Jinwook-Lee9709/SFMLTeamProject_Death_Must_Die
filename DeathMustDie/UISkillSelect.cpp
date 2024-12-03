#include "stdafx.h"
#include "UISkillSelect.h"

UISkillSelect::UISkillSelect(const std::string& name)
	: UIPopup(name)
{
}

void UISkillSelect::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UISkillSelect::SetRotation(float angle)
{
	rotation = angle;
}

void UISkillSelect::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UISkillSelect::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UISkillSelect::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UISkillSelect::Init()
{
}

void UISkillSelect::Release()
{
	panels.clear();
}

void UISkillSelect::Reset()
{
	sf::Vector2f initPos = { 300.f, 100.f };
	for (int i = 0; i < 3; i++)
	{
		SkillSelectPanel panel;
		panel.Reset();
		panel.SetPosition(initPos);
		panel.SetScale({ 1.f, 1.f });
		initPos.x += 500.f;
		panels.push_back(panel);
	}
}

void UISkillSelect::Update(float dt)
{
	for (auto& panel : panels)
	{
		panel.Update(dt);
	}
}

void UISkillSelect::Draw(sf::RenderWindow& window)
{
	for (auto& panel : panels)
	{
		panel.Draw(window);
	}
}
