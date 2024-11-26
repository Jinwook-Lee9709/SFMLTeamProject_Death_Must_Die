#pragma once
enum class LoopType {
	Loop,
	Single
};


struct AnimationFrame
{
	std::string texId;
	sf::IntRect texCoord;
	AnimationFrame();
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord)
		:texId(texId), texCoord(texCoord) {}
};

struct AnimationClip
{
	LoopType loopType = LoopType::Loop;
	int fps = 30;
	std::vector<AnimationFrame> frames;
};

