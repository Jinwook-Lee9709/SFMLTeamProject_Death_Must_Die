#pragma once
class DataTable
{
public:
	enum class Types
	{
		String, 
	};
	static const int TotalTypes = 1;

protected:
	Types type;


public:
	DataTable(Types t) : type(t) {};
	~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;
};

