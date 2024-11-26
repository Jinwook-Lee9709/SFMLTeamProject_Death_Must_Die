#include "stdafx.h"
#include "AnimationClip.h"

bool AnimationClip::loadFromFile(const std::string& animationId)
{
	rapidcsv::Document Doc("tables/animations.csv", rapidcsv::LabelParams(0, 0));
	auto row =  Doc.GetRow<std::string>(animationId);
	id = animationId;
	loopType = (AnimationLoopTypes)std::stoi(row[1]);
	fps = std::stoi(row[0]);
	int width = std::stoi(row[4]);
	int height = std::stoi(row[5]);
	int sheetWidth = width * std::stoi(row[2]);

	frames.clear();


	sf::IntRect texCoord = { 0, 0, width, height };
	for (int i = 0; i < std::stoi(row[3]); i++) 
	{
		frames.push_back({animationId, texCoord});
		texCoord.left += width;
		if (texCoord.left == sheetWidth)
		{
			texCoord.left = 0;
			texCoord.top += height;
		}
	}
	return true;
}
