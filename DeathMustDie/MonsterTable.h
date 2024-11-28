#pragma once

class MonsterTable : public DataTable
{
public:
	static std::wstring Undefined;

protected:
	std::unordered_map<std::string, std::vector<std::wstring>> table;

	std::string filePath = "tables/monster_table.json";

public:
	MonsterTable() : DataTable(DataTable::Types::Monster) {};
	~MonsterTable() = default;

	bool Load() override;
	void Release() override;

	const std::wstring& Get(const std::string& id);
	const std::wstring& Get(const std::string& id, Languages lang);

};

