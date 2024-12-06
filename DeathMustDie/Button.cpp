#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& name)
	: GameObject("Button" + name)
{

}

void Button::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.SetPosition(pos);
}

void Button::SetRotation(float angle)
{
	rotation = angle;
	text.SetRotation(rotation);
}

void Button::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.SetScale(scale);
}

void Button::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		text.SetOrigin(originPreset);
	}
}

void Button::SetOrigin(const sf::Vector2f& newOrigin)
{
	this->origin = newOrigin;
	originPreset = Origins::Custom;
	text.SetOrigin(origin);
}

void Button::Init()
{
}

void Button::Release()
{
}

void Button::Reset()
{
	text.SetFillColor(sf::Color::White);
}

void Button::Update(float dt)
{
	if (text.GetGlobalBounds().contains(UI_MOUSE_POS))
	{
		text.SetFillColor(sf::Color(62, 197, 241, 255));
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			EVENT_HANDLER.InvokeEvent(name + "Pressed");
		}
	}
	else
	{
		text.SetFillColor(sf::Color::White);
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	text.Draw(window);
}

void Button::SetFont(std::string fontId)
{
	text.SetFont(GET_FONT(fontId));
}

void Button::SetString(std::string stringId)
{
	text.SetString(stringId);
}

void Button::SetCharacterSize(int size)
{
	text.SetCharacterSize(size);
}

