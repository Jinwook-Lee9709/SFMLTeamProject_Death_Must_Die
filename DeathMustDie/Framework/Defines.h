#pragma once

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

enum class AbilitySpawnType
{
	BasicAttack,
	OnRandomEnemy, 
	OnCharacter,
	CharacterToMouse, 
};

enum class AbilityTriggerType
{
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

enum class MonsterTypes
{
	None = -1,
	Skeleton,
	Slime,
	Count,
};
