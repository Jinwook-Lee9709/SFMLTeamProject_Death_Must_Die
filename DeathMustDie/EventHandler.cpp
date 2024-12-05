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

void EventHandler::AddEventInt(const std::string& id, std::function<void(const int&)> action)
{
	auto it = eventsInt.find(id);
	if (it == eventsInt.end()) {
		eventsInt.emplace(id, std::vector<std::function<void(const int&)>>{action});
	}
	else {
		it->second.push_back(action);
	}
}

void EventHandler::DeleteEvent(const std::string& id)
{
	auto it1 = events.find(id);
	if (it1 == events.end()) {
		return;
	}
	else {
		it1->second.clear();
		events.erase(it1);
	}
	auto it2 = eventsGo.find(id);
	if (it2 == eventsGo.end()) {
		return;
	}
	else {
		it2->second.clear();
		eventsGo.erase(it2);
	}
	auto it3 = eventsInt.find(id);
	if (it3 == eventsInt.end()) {
		return;
	}
	else {
		it3->second.clear();
		eventsInt.erase(it3);
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

void EventHandler::InvokeEvent(const std::string& id, const int& num)
{
	auto it = eventsInt.find(id);
	if (it == eventsInt.end())
		return;
	for (auto func : it->second)
	{
		func(num);
	}
}
