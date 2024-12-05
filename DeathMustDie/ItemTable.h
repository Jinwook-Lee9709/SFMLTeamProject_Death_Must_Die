#pragma once

class ItemTable : public DataTable
{
protected:
	json TABLE;
public:
	ItemTable() : DataTable(DataTable::Types::Item) {};
	~ItemTable() = default;

	bool Load() override;
	void Release() override;

	const json& Get(const std::string& id);
};

