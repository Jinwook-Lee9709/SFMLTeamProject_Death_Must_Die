#pragma once

class MonsterTable : public DataTable
{
protected:
	json TABLE;
public:
	MonsterTable() : DataTable(DataTable::Types::Monster) {};
	~MonsterTable() = default;

	bool Load() override;
	void Release() override;

	const json& Get(const std::string& id);

};

