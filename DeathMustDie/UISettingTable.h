#pragma once
#include "DataTable.h"
class UISettingTable :
    public DataTable
{
protected:
    json TABLE;
public:
    UISettingTable() : DataTable(DataTable::Types::SkillSetting) {};
    ~UISettingTable() = default;

    bool Load() override;
    void Release() override;

    bool Reload();

    const json& Get(const std::string& PanelName);

};

