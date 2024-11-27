#pragma once
#include "GameObject.h"
class AttackEntity :
    public GameObject
{
protected:


public:
    AttackEntity(const std::string& name);
    ~AttackEntity() = default;

    virtual void SetInfo(const json& j) {}

};

