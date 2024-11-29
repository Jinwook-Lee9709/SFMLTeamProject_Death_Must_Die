#include "stdafx.h"
#include "Calculator.h"

void Calculator::AddEffect(const Effect& effect)
{
	for (auto& it : effects)
	{
		if (it.source == effect.source)
		{
			switch (it.type)
			{
				case EffectType::Skill:
				{
					it = effect;
					break;
				}
				case EffectType::Permanent:
				{
					it.multiplier += effect.multiplier - 1;
					break;
				}
				case EffectType::Temporary:
				{
					it.duration = effect.duration;
					break;
				}
			}
			return;
		}
	}
	effects.push_back(effect);
}

float Calculator::CalculateValue(float base)
{
	float value = base;
	for (auto& effect : effects)
	{
		value *= effect.multiplier;
	}
	return value;
}

void Calculator::Update(float dt)
{
	auto it = effects.begin();
	while (it != effects.end())
	{
		if (it->type == EffectType::Temporary)
		{
			it->duration -= dt;
			if (it->duration <= 0)
			{
				it = effects.erase(it);
				continue;
			}
		}
		it++;
	}
}
