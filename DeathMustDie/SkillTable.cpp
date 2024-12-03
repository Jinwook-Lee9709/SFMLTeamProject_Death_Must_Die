#include "stdafx.h"
#include "SkillTable.h"

bool SkillTable::Load()
{
	std::ifstream file1("tables/skill_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;
}

void SkillTable::Release()
{
	TABLE.clear();
}

const json& SkillTable::Get(const std::string& skillId)
{
	return TABLE[skillId];
}

const json& SkillTable::GetAll()
{
	return TABLE;
}
