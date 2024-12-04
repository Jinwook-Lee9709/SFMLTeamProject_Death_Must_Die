#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& name)
	:GameObject(name)
{
}

void Item::Draw(sf::RenderWindow& window)
{
}

void Item::OnActtive()
{
	active = true;
}
