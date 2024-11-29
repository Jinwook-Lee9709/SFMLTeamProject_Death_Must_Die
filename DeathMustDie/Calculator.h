#pragma once
enum class EffectType
{
	Skill,
	Permanent,
	Temporary
};


struct Effect
{
	EffectType type;
	float multiplier;  
	int duration;    
	std::string source;
	Effect(EffectType type, float multiplier, float duration, std::string source)
		:type(type), multiplier(multiplier), duration(duration), source(source)
	{}
};

class Calculator
{
private:
	float base;
	std::vector<Effect> effects;
	void AddEffect(const Effect& effect);
	float CalculateValue();

	void Update(float dt);

};

