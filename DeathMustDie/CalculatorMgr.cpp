#include "stdafx.h"
#include "CalculatorMgr.h"
CalculatorMgr::CalculatorMgr()
{
	for (int i = 0 ; i<(int)ValueType::Count ; i++)
	{
		container.insert({ (ValueType)i, Calculator() });
	}
}

void CalculatorMgr::Update(float dt)
{
	for (auto& calcuator : container)
	{
		calcuator.second.Update(dt);
	}
}

void CalculatorMgr::Release()
{
	container.clear();
}

void CalculatorMgr::AddEffect(const ValueType& type, const Effect& effect)
{
	container[type].AddEffect(effect);
}

float CalculatorMgr::GetValue(const ValueType& type, float value)
{
	return container[type].CalculateValue(value);
}
