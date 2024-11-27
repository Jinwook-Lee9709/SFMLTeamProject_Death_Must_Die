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

enum class MonsterTypes
{
	None = -1,
	Skeleton,
	Slime,
	Count,
};
