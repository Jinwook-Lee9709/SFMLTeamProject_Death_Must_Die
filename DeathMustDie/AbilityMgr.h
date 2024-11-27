#pragma once
class AbilityMgr
{
	std::vector<std::function<void()>> attack;
	std::vector<std::function<void()>> dash;
	std::vector<std::function<void()>> strike;
	std::vector<std::function<void()>> cast;

};

