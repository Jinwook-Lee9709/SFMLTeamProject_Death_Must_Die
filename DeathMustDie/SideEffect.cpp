#include "stdafx.h"
#include "SideEffect.h"
#include "Monster.h"

void SE_Debuff::SetInfo(const json& j)
{
	this->info = j;
}

void SE_Debuff::TriggerEffect(const std::vector<Monster*>& monsters)
{
	DebuffType type = info["debuffType"].get<DebuffType>();
	for (auto& monster : monsters)
	{
		monster->OnDebuffed(DebuffType::Burn);
	}
}
