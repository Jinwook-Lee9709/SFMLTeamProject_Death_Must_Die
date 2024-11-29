#include "stdafx.h"
#include "Monster.h"
#include "SceneDev2.h"

Monster::Monster(const std::string& name)
	:GameObject(name)
{
	HPBar.setSize({65, 10});
	HPBarFrame.setSize({65, 10});
	
	HPBar.setFillColor(sf::Color::Red);
	HPBarFrame.setFillColor(sf::Color::Black);

	Utils::SetOrigin(HPBar, Origins::BC);
	Utils::SetOrigin(HPBarFrame, Origins::BC);
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(HPBarFrame);
	window.draw(HPBar);
}
