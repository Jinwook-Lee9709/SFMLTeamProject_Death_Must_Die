#include "stdafx.h"
#include "UISettingTable.h"

bool UISettingTable::Load()
{
	std::ifstream file1("tables/ui_setting.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;
}

void UISettingTable::Release()
{
	TABLE.clear();
}

bool UISettingTable::Reload()
{
	std::ifstream file1("tables/ui_setting.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
		return false;
	}
	TABLE = json::parse(file1);
	file1.close();
	return true;
}

const json& UISettingTable::Get(const std::string& PanelName)
{
	return TABLE[PanelName];
}
