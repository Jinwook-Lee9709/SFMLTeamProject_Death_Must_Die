#include "stdafx.h"
#include "Structure.h"

Structure::Structure(const std::string& name)
	: GameObject(name)
{
}

void Structure::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Structure::SetRotation(float angle)
{
	rotation = angle;
}

void Structure::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Structure::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Structure::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Structure::Init()
{
}

void Structure::Release()
{
}

void Structure::Reset()
{
}

void Structure::Update(float dt)
{
}

void Structure::Draw(sf::RenderWindow& window)
{
}
