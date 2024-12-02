#include "stdafx.h"
#include "MonsterTable.h"


bool MonsterTable::Load()
{
	Release();
	std::ifstream file1("tables/monster_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;

	return true;
}


void MonsterTable::Release()
{
	TABLE.clear();
}

const json& MonsterTable::Get(const std::string& monsterId)
{
	return TABLE[monsterId];
}

