#include "stdafx.h"
#include "AttackEntity.h"
#include "MonsterPoolManager.h"
#include "SideEffect.h"

int AttackEntity::entityCount = 0;

AttackEntity::AttackEntity()
	:GameObject("AttackEntity" + std::to_string(entityCount))
{
	entityCount++;
	monsters = dynamic_cast<MonsterPoolManager*>(SCENE_MGR.GetCurrentScene()->FindGo("monsterPoolMgr"));
}

AttackEntity::~AttackEntity()
{
	delete sideEffect;
}

void AttackEntity::SetSideEffect(const json& j)
{
	SideEffectType type = j["effectType"].get<SideEffectType>();
	switch (type)
	{
		case SideEffectType::Debuff:
		{
			sideEffect = new SE_Debuff();
			sideEffect->SetInfo(j);
			break;
		}
		case SideEffectType::None:
		{
			sideEffect = new SE_Null();
			break;
		}
	}
}
