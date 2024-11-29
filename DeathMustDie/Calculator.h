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
	std::vector<Effect> effects;
public:
	void AddEffect(const Effect& effect);
	float CalculateValue(float base);
	void Update(float dt);

};

