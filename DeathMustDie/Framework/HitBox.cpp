#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox()
{
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.f);
}

bool HitBox::CheckContains(sf::Vector2f coord)
{
	rect.getGlobalBounds().contains(coord);
	return false;
}

bool HitBox::isClicked()
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left)) {
		sf::Vector2f pos = (sf::Vector2f)InputMgr::GetMousePosition();
		if (rect.getGlobalBounds().contains(pos)) {
			return true;
		}

	}
	return false;
}

void HitBox::UpdateTr(const sf::Transformable& tr, const sf::FloatRect& localBounds)
{
	rect.setOutlineColor(sf::Color::Green);
	rect.setSize({ localBounds.width, localBounds.height });
	rect.setOrigin(tr.getOrigin());
	rect.setPosition(tr.getPosition());
	rect.setScale(tr.getScale());
	rect.setRotation(tr.getRotation());
}

void HitBox::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
		window.draw(rect);
}
