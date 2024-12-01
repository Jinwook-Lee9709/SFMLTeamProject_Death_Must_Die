#pragma once
#include "Calculator.h"

enum class ValueType
{
	Attack,
	Dash,
	Strike,
	Cast,
	Power,
	Summon,
	Passive,
	BaseDamage,
	Count
};

class CalculatorMgr : public GameObject
{
protected:
	std::unordered_map<ValueType, Calculator> container;
public:
	CalculatorMgr(const std::string& name = "");
	~CalculatorMgr() = default;
	void Update(float dt) override;
	void Release() override;
	void AddEffect(const ValueType& type, const Effect& effect);
	float GetValue(const ValueType& type, float value);
	float GetValue(const AbilityType& type, float value);
};

