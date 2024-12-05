#pragma once

struct Experience
{
	int level;
	int curExp;
	int sumExp;
};

class ExpTable : public DataTable
{
public:
	static Experience Undefined;
protected:
	
	std::unordered_map<int, Experience> table;

	std::string filePath = "tables/exp_table.csv";

public:
	ExpTable() : DataTable(DataTable::Types::Exp) { };
	~ExpTable() = default;

	bool Load() override;
	void Release() override;

	const Experience& Get(int id);
};
