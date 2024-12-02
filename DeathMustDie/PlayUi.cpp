#include "stdafx.h"
#include "PlayUi.h"

PlayUi::PlayUi(const std::string& name)
	: GameObject(name)
{
}

void PlayUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void PlayUi::SetRotation(float angle)
{
	rotation = angle;
}

void PlayUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void PlayUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void PlayUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void PlayUi::Init()
{
}

void PlayUi::Release()
{
}

void PlayUi::Reset()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void PlayUi::Update(float dt)
{
}

void PlayUi::Draw(sf::RenderWindow& window)
{
}
