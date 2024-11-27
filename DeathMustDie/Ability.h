#pragma once
enum class AbilityGrade
{
	Novice,
	Adept,
	Expert,
	Master,
	Legend,
};

enum class AbilityType
{
	Attack,
	Dash,
	Strike,
	Cast,
	Power,
	Summon,
	Passive,
};

enum class AbilityAction
{
	Fire,
	Random,
	fall,
	Radial,
	Wedge,
	Chain,
	Summon,
	Buff,
	Shield
};

class Ability : public GameObject
{
protected:
	AbilityGrade grade;
	AbilityType type;
	AbilityAction action;

public:
	Ability(const AbilityType type,
		const AbilityGrade& grade = AbilityGrade::Novice,
		const std::string& name = ""
		);
	~Ability() = default;

	void SetSkillInfo();

	AbilityGrade GetGrade() const { return this->grade; }
	void SetGrade(const AbilityGrade& grade) { this->grade = grade; }
	AbilityType GetType() const { return type; }
};

