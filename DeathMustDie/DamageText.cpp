#include "stdafx.h"
#include "DamageText.h"

DamageText::DamageText(const std::string& name)
	: GameObject(name), text("")
{
}

void DamageText::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.SetPosition(position);
}

void DamageText::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.SetScale(scale);
}

void DamageText::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		text.SetOrigin(preset);
	}
}

void DamageText::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.SetOrigin(origin);
}

void DamageText::Init()
{
}

void DamageText::Release()
{
}

void DamageText::Reset()
{
	text.SetFont("Bokor");
	text.SetCharacterSize(40);
	text.SetOutline(2, sf::Color::Black);
}

void DamageText::Update(float dt)
{
	if (!isPlay && !playQueue.empty())
	{
		PlayAnimation(playQueue.front());
		playQueue.pop();
	}
	if (isPlay) {
		timer += dt;
		posForAnim += sf::Vector2f(0, -120 * dt);
		text.SetPosition(position + posForAnim);
		if (timer > duration)
		{
			isPlay = false;
			this->active = false;
		}

	}
}

void DamageText::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		text.Draw(window);
	}
}

void DamageText::AddAnimation(int type)
{
	playQueue.push(type);
}

void DamageText::PlayAnimation(int type)
{
	timer = 0;
	isPlay = true;
	this->active = true;
	posForAnim = { 0.f, 0.f };
	SetText(type);
}

void DamageText::SetText(int type)
{

	switch (type)
	{
		case 0:
		{
			text.SetString(std::to_wstring(type));
			text.SetFillColor(sf::Color(1, 4, 7, 255));
			text.SetOutline(2, sf::Color(147, 147, 147, 255));
			break;
		}
		default :
		{
			if (type > 0) 
			{
				text.SetString(std::to_wstring(type));
				text.SetFillColor(sf::Color(197, 7, 0, 255));
				text.SetOutline(2, sf::Color(sf::Color::Black));
			}
			else
			{
				text.SetString(std::to_wstring(abs(type)));
				text.SetFillColor(sf::Color::Green);
				text.SetOutline(2, sf::Color(sf::Color::Black));
			}
			
		}

	}
	SetOrigin(originPreset);
}
