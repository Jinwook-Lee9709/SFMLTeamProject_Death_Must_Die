#pragma once
#include "GameObject.h"
#include "MonsterPoolManager.h"
#include "SideEffect.h"


class AttackEntity :
    public GameObject
{
protected:
    MonsterPoolManager* monsters;
    SideEffect* sideEffect;
    static int entityCount;
public:
    AttackEntity();
    ~AttackEntity();

    virtual void SetInfo(const json& j) {}
    virtual void ChangeInfo(const json& j) {}
    virtual void Activate() {}
    virtual void SetSideEffect(const json& j);
};

