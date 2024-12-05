#include "stdafx.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "SkillTable.h"
#include "MonsterTable.h"
#include "UISettingTable.h"
#include "SkillLevelTable.h"

#include "ItemTable.h"
#include "ExpTable.h"
DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();

	tables.insert({ DataTable::Types::String, new StringTable() });
	tables.insert({ DataTable::Types::Skill, new SkillTable() });
	tables.insert({ DataTable::Types::Monster, new MonsterTable() });
	tables.insert({ DataTable::Types::SkillSetting, new UISettingTable() });
	tables.insert({ DataTable::Types::SkillLevel, new SkillLevelTable() });
	tables.insert({ DataTable::Types::Item, new ItemTable() });
	tables.insert({ DataTable::Types::Exp, new ExpTable() });

	for (auto t : tables)
	{
		t.second->Load();
	}
}

void DataTableMgr::Release()
{
	for (auto t : tables)
	{
		t.second->Release();
		delete t.second;
	}
	tables.clear();
}
