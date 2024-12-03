#pragma once
#include "DataTable.h"
class SkillTable :
    public DataTable
{
protected:
    json TABLE;
public:
    SkillTable() : DataTable(DataTable::Types::Skill){};
    ~SkillTable() = default;

    bool Load() override;
    void Release() override;

    const json& Get(const std::string& skillId);
    const json& GetAll();
};

