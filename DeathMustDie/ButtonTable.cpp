#include "stdafx.h"
#include "ButtonTable.h"

bool ButtonTable::Load()
{
	std::ifstream file1("tables/button_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;
}

void ButtonTable::Release()
{
	TABLE.clear();
}

const json& ButtonTable::Get(const std::string& button)
{
	return TABLE[button];
}

const json& ButtonTable::GetAll()
{
	return TABLE;
}
