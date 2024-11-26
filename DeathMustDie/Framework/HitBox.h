#pragma once

class HitBox
{
public:
	HitBox();

	sf::RectangleShape rect;

	bool CheckContains(sf::Vector2f coord);
	bool isClicked();
	void UpdateTr(const sf::Transformable& tr, const sf::FloatRect& localBound);
	void Draw(sf::RenderWindow& window);
};