#include "stdafx.h"
#include "ExpTable.h"
#include "rapidcsv.h"

Experience ExpTable::Undefined;

bool ExpTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<int>(i);
		int id = row[0];
		if (table.find(id) != table.end())
		{
			return false;
		}

		table[id].level = row[0];
		table[id].curExp = row[1];
		table[id].sumExp = row[2];
	}

	return true;
}


void ExpTable::Release()
{
	table.clear();
}

const Experience& ExpTable::Get(int id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}
