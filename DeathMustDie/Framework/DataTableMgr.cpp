#include "stdafx.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "SkillTable.h"
#include "MonsterTable.h"
#include "ItemTable.h"
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
	tables.insert({ DataTable::Types::Item, new ItemTable() });

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
