#include "stdafx.h"
#include "Gem.h"
#include "AniSkeleton.h"

Gem::Gem(const std::string& name)
	:Item(name)
{
}

void Gem::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Gem::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Gem::SetScale(const sf::Vector2f& size)
{
	scale = size;
	body.setScale(scale);
}

void Gem::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Gem::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(newOrigin);
}

sf::FloatRect Gem::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Gem::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Gem::SetInfo(const json& j)
{
	this->j = j;
}

void Gem::Reset()
{
	body.setTexture(TEXTURE_MGR.Get("resource/texture/Sprite/gem.png"));
	SetOrigin(Origins::MC);
	active = true;
}

void Gem::Update(float dt)
{

}

void Gem::FixedUpdate(float dt)
{
}

void Gem::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
