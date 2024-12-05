#pragma once

class Monster;

enum class SideEffectType
{
	None = -1,
	Debuff,
};


class SideEffect
{
protected:
	json info;
public:
	SideEffect() = default;
	~SideEffect() = default;
	virtual void SetInfo(const json& j) {};
	virtual void TriggerEffect(const std::vector<Monster*>& monsters) {};
};

class SE_Null : public SideEffect
{
public:
	SE_Null() {};
	void SetInfo(const json& j) override {};
	void TriggerEffect(const std::vector<Monster*>& monsters) override {};
};

class SE_Debuff : public SideEffect
{
	void SetInfo(const json& j) override;
	void TriggerEffect(const std::vector<Monster*>& monsters) override;
};
