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
	text.SetFont(GET_FONT("PerfectDOSVGA437"));
	text.SetCharacterSize(30);
	text.SetOutline(1, sf::Color::Black);
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
		if (timer > duration - 0.2f)
		{
			opacity -= 1225 * dt;
			if (opacity < 0)
				opacity = 0;
			text.SetOpacity(opacity);
		}

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
	opacity = 255;
	SetText(type);
}

void DamageText::SetText(int type)
{
	if (type > 0) 
	{
		text.SetString(std::to_wstring(type));
		text.SetFillColor(sf::Color::White);
		text.SetOutline(2, sf::Color(sf::Color::Black));
	}
	SetOrigin(originPreset);
}
