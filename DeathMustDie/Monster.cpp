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

    collisionCircle.setRadius(collisionRadius);
    collisionCircle.setOrigin(collisionRadius, collisionRadius);
}


void Monster::SetCollisionRadius(float radius) 
{
    collisionRadius = radius;
    collisionCircle.setRadius(radius);
    collisionCircle.setOrigin(radius, radius);
}

sf::CircleShape Monster::GetCollisionCircle() const 
{
    sf::CircleShape circle = collisionCircle;
    circle.setPosition(position);
    return circle;
}

bool Monster::CheckCollision(const Monster& other) const 
{
    sf::Vector2f delta = other.position - position; // �� ������ �Ÿ� ���
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    float radiusSum = collisionRadius + other.collisionRadius;

    return distanceSquared <= (radiusSum * radiusSum); // �浹 ���� ��ȯ
}

void Monster::OnCollision(Monster* other) 
{
    std::cout << "Collision with another monster!" << std::endl;
    sf::Vector2f delta = position - other->position;
    Utils::Normalize(delta);
    position += delta * 10.0f; // �浹 �ݹ� �Ÿ� ����
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(HPBarFrame);
	window.draw(HPBar);
    window.draw(collisionCircle);
}

void Monster::OnDeath()
{
	active = false; // ��Ȱ��ȭ
	EVENT_HANDLER.InvokeEvent("OnMonsterDie", (GameObject)*this);
}

void Monster::OnSummon()
{
    EVENT_HANDLER.InvokeEvent("SummonSkeleton", (GameObject)*this);
}

