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

void EventHandler::AddEventGo(const std::string& id, std::function<void(const GameObject&)> action)
{
	auto it = eventsGo.find(id);
	if (it == eventsGo.end()) {
		eventsGo.emplace(id, std::vector<std::function<void(const GameObject&)>>{action});
	}
	else {
		it->second.push_back(action);
	}
}

void EventHandler::DeleteEvenet(const std::string& id)
{
	auto it = events.find(id);
	if (it == events.end()) {
		return;
	}
	else {
		it->second.clear();
		events.erase(it);
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

void EventHandler::InvokeEvent(const std::string& id, const GameObject& go)
{
	auto it = eventsGo.find(id);
	if (it == eventsGo.end())
		return;
	for (auto func : it->second)
	{
		func(go);
	}
}
