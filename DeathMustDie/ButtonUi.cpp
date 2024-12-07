#include "stdafx.h"
#include "ButtonUi.h"

ButtonUi::ButtonUi(const std::string& name)
	: GameObject(name)
{
}

void ButtonUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.SetPosition({ position.x - 20.f, position.y });
	buttonName.SetPosition({ position.x + 20.f, position.y });
}

void ButtonUi::SetRotation(float angle)
{
	rotation = angle;
}

void ButtonUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.SetScale(scale);
	buttonName.SetScale(scale);
}

void ButtonUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void ButtonUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void ButtonUi::Init()
{
	BTN_TABLE->Load();
	RES_TABLE_MGR.LoadScene("UI");
	
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void ButtonUi::Release()
{
}

void ButtonUi::Reset()
{
	body = SpriteGo("buttonSpr");
	body.Reset();
	buttonName = TextGo("PtSerifRegular_Font");
	buttonName.Reset();

	body.SetOrigin(Origins::MR);
	buttonName.SetOrigin(Origins::ML);

	SetScale({ 0.8f, 0.8f });
	trans = 255;
	buttonVisible = false;
}

void ButtonUi::Update(float dt)
{
	if (!IsActive())
		return;
	if (buttonVisible)
	{
		trans = Utils::Lerp(trans, 0, 0.0001f, false);
		body.SetFillColor(sf::Color(255, 255, 255, trans));
		buttonName.SetFillColor(sf::Color(255, 255, 255, trans));
	}
	if (trans <= 0)
	{
		SetActive(false);
	}
	
}

void ButtonUi::Draw(sf::RenderWindow& window)
{
	if (!IsActive())
		return;
	body.Draw(window);
	buttonName.Draw(window);
}

void ButtonUi::SetButton(const std::string& btnName)
{
	this->btnName = btnName;
	json j = BTN_TABLE->Get(this->btnName);
	body.SetTextureRect({ j[0], j[1], j[2], j[3] });
	body.SetOrigin(Origins::MR);
}

void ButtonUi::SetButtonName(const std::wstring& btnName)
{
	buttonName.SetString(btnName);
	buttonName.SetOrigin(Origins::ML);
}
