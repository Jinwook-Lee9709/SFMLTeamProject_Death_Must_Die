#pragma once
class DataTableMgr : public Singleton<DataTableMgr>
{
	friend Singleton<DataTableMgr>;

private:
	DataTableMgr() = default;
	~DataTableMgr() ;
	DataTableMgr(const DataTableMgr&) = delete;
	DataTableMgr& operator=(const DataTableMgr&) = delete;

	std::unordered_map <DataTable::Types, DataTable*> tables;
public:
	void Init();
	void Release();

	template<typename T>
	T* Get(DataTable::Types type);

};

template<typename T>
inline T* DataTableMgr::Get(DataTable::Types type)
{
	auto find = tables.find(type);
	if (find == tables.end()) {
		return nullptr;
	}
	return dynamic_cast<T*>(find->second);
}

#define DATATABLE_MGR (DataTableMgr::Instance())
#define STRING_TABLE (DATATABLE_MGR.Get<StringTable>(DataTable::Types::String))
#define SKILL_TABLE (DATATABLE_MGR.Get<SkillTable>(DataTable::Types::Skill))
#define MONSTER_TABLE (DATATABLE_MGR.Get<MonsterTable>(DataTable::Types::Monster))
#define UI_SETTING_TABLE (DATATABLE_MGR.Get<UISettingTable>(DataTable::Types::SkillSetting))
#define SKILL_LEVEL_TABLE (DATATABLE_MGR.Get<SkillLevelTable>(DataTable::Types::SkillLevel))
#define ITEM_TABLE (DATATABLE_MGR.Get<ItemTable>(DataTable::Types::Item))
#define EXP_TABLE (DATATABLE_MGR.Get<ExpTable>(DataTable::Types::Exp))
#define BTN_TABLE (DATATABLE_MGR.Get<ButtonTable>(DataTable::Types::Button))
#define STR(X) (STRING_TABLE->Get(X))