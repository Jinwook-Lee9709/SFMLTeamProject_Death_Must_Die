#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name)
	:GameObject(name), textureId(texId)
{

}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(sprite, originPreset);
	}
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void SpriteGo::FlipX(bool flag)
{
	GameObject::FlipX(flag);
	sprite.setScale(scale);
}

void SpriteGo::FlipY(bool flag)
{
	GameObject::FlipY(flag);
	sprite.setScale(scale);
}

void SpriteGo::Reset()
{
	sprite.setTexture(GET_TEX(textureId), true);
	SetOrigin(originPreset);
	hitbox.UpdateTr(sprite, sprite.getGlobalBounds());
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	sprite.setScale(scale);
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(sprite);
	}
	hitbox.Draw(window);
}

sf::FloatRect SpriteGo::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect SpriteGo::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void SpriteGo::SetFillColor(const sf::Color& color)
{
	sprite.setColor(color);
}

void SpriteGo::ChangeTexture(const std::string& texId)
{
	if (textureId != texId)
	{
		this->textureId = texId;
		Reset();
	}

}

sf::Vector2f SpriteGo::GetSize()
{
	return (sf::Vector2f)sprite.getTexture()->getSize();
}
