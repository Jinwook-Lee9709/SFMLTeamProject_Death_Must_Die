#include "stdafx.h"
#include "Monster.h"
#include "SceneDev2.h"
#include "MonsterSpawner.h"

Monster::Monster(const std::string& name)
	:GameObject(name)
{
	HPBar.setSize({ 65, 10 });
	HPBarFrame.setSize({ 65, 10 });

	HPBar.setFillColor(sf::Color::Red);
	HPBarFrame.setFillColor(sf::Color::Black);

	Utils::SetOrigin(HPBar, Origins::BL);
	Utils::SetOrigin(HPBarFrame, Origins::BL);
}



void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(HPBarFrame);
	window.draw(HPBar);
}

void Monster::OnDeath()
{
	active = false; // 비활성화
}

