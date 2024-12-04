#include "stdafx.h"
#include "SkillLevelTable.h"

bool SkillLevelTable::Load()
{
	Release();
	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);
		if (it != table.end())
		{
			std::cout << "스트링 테이블 키 중복!" << std::endl;
			return false;
		}
		for (int j = 0; j < (int)AbilityGrade::Count-1; ++j)
		{
			auto& vec = table[strings[0]];
			vec.resize((int)Languages::Count-1);
			vec[j] = stof(strings[j + 1]);
		}
	}

	return true;
}

void SkillLevelTable::Release()
{
	table.clear();
}

const float& SkillLevelTable::Get(const std::string& id, AbilityGrade grade)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return -1;
	}
	//return find->second;
	return (find->second)[(int)grade];
}
