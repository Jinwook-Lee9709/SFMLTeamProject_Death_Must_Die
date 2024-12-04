#pragma once
#include "DataTable.h"
class SkillLevelTable :
    public DataTable
{
protected:
    std::unordered_map<std::string, std::vector<float>> table;

    std::string filePath = "tables/skill_level_table.csv";

public:
    SkillLevelTable() : DataTable(DataTable::Types::SkillLevel) {};
    ~SkillLevelTable() = default;

    bool Load() override;
    void Release() override;

    const float& Get(const std::string& id, AbilityGrade);

};

