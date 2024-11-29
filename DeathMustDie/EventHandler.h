#pragma once

class EventHandler: public Singleton<EventHandler>
{
	friend Singleton<EventHandler>;
protected:
	std::unordered_map<std::string, std::vector<std::function<void()>>> events;

	EventHandler() = default;
	virtual ~EventHandler() = default;

	EventHandler(const EventHandler& other) = delete;
	EventHandler& operator=(const EventHandler& other) = delete;

public:
	void AddEvent(const std::string& id, std::function<void()>action);
	void InvokeEvent(const std::string& id);
};

