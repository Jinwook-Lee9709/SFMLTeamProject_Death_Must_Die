#pragma once

#define VAR_TO_STRING(var) #var

enum class Languages
{
	Korean,
	English,
	Count
};


enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class SceneIds
{
	None = -1,
	Game,
	Dev1,
	Dev2,
	Dev3,
	Title,
	Count,
};

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};


enum class AbilityGrade
{
	Novice,
	Adept,
	Expert,
	Master,
	Legend,
	Count
};

inline AbilityGrade& operator++(AbilityGrade& abilitiy) {
	if (abilitiy == AbilityGrade::Legend) {
		throw std::out_of_range("Cannot increment beyond the last enum value.");
	}
	abilitiy = (AbilityGrade)((int)(abilitiy) + 1);
	return abilitiy;
}
inline AbilityGrade& operator--(AbilityGrade& abilitiy) {
	if (abilitiy == AbilityGrade::Novice) {
		throw std::out_of_range("Cannot decrement Before the first enum value.");
	}
	abilitiy = (AbilityGrade)((int)(abilitiy)-1);
	return abilitiy;
}

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

enum class AbilitySpawnType
{
	BasicAttack,
	OnRandomEnemy, 
	OnUser,
	UserToMouse,
	ClosestEnemy
};

enum class AbilityTriggerType
{
	BasicAttack,
	Attack, // When Hit enemy
	Dash, // When Dash
	AutoCast, //Actiavte by CoolTime
	Earn, // Only activates when earning a skill
};

enum class AttackEntityType
{
	Projectile,
	Circle,
	Fall,
	Wedge,
	Trail,
	Summon,
	BasicAttack,
};

enum class UpgradeType
{
	Earn,
	LevelUp,
	GradeUp
};

enum class IncreaseType
{
	CastDamage,
};

enum class DebuffType
{
	Burn
};


enum class MonsterTypes
{
	None = -1,
	Skeleton,
	Slime,
	Boss,
	Count,
};

enum class ItemTypes
{
	None = -1,
	Gem,
	Heart,
};
