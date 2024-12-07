#pragma once
#include "DataTable.h"
class ButtonTable :
    public DataTable
{
protected:
    json TABLE;
public:
    ButtonTable() : DataTable(DataTable::Types::Button) {};
    ~ButtonTable() = default;

    bool Load() override;
    void Release() override;

    const json& Get(const std::string& button);
    const json& GetAll();
};
