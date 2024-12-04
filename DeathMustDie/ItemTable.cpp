#include "stdafx.h"
#include "ItemTable.h"

bool ItemTable::Load()
{
	Release();
	std::ifstream file1("tables/item_table.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;

	return true;
}

void ItemTable::Release()
{
	TABLE.clear();
}

const json& ItemTable::Get(const std::string& itemId)
{
	return TABLE[itemId];
}
