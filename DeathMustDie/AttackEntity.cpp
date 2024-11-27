#include "stdafx.h"
#include "AttackEntity.h"

AttackEntity::AttackEntity(const std::string& name)
	:GameObject(name)
{
	animator.SetTarget(&sprite);
}

void AttackEntity::Update(float dt)
{
	animator.Update(dt);
}

void AttackEntity::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
