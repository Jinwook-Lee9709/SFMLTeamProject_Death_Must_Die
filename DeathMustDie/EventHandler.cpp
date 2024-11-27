#include "stdafx.h"
#include "EventHandler.h"

void EventHandler::AddEvent(const std::string& id, std::function<void()> action)
{
	auto it = events.find(id);
	if (it == events.end()) {
		events.emplace(id, std::vector<std::function<void()>>{action});
	}
	else {
		it->second.push_back(action);
	}
}

void EventHandler::InvokeEvent(const std::string& id)
{
	auto it = events.find(id);
	if (it == events.end())
		return;
	for (auto func : it->second)
	{
		func();
	}
}
