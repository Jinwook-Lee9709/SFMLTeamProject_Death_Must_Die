#pragma once
#include "Calculator.h"

enum class ValueType
{
	None = -1,
	MinDamage,
	MaxDamage,
	Attack,
	Dash,
	Strike,
	Cast,
	Power,
	Summon,
	Passive,
	Count
};

class CalculatorMgr : public GameObject
{
protected:
	std::unordered_map<ValueType, Calculator> container;
public:
	CalculatorMgr();
	~CalculatorMgr() = default;
	void Update(float dt) override;
	void Release() override;
	void AddEffect(const ValueType& type, const Effect& effect);
	float GetValue(const ValueType& type, float value);
};

