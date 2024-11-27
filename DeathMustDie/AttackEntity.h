#pragma once
#include "GameObject.h"
class AttackEntity :
    public GameObject
{
protected:
    sf::Sprite sprite;
    Animator animator;

public:
    AttackEntity(const std::string& name);
    ~AttackEntity() = default;

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

};

