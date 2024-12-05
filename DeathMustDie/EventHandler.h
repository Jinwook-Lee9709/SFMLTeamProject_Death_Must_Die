#pragma once
class GameObject;

class GameObject;

class EventHandler: public Singleton<EventHandler>
{
	friend Singleton<EventHandler>;
protected:
	std::unordered_map<std::string, std::vector<std::function<void()>>> events;
	std::unordered_map<std::string, std::vector<std::function<void(const GameObject&)>>> eventsGo;
	std::unordered_map<std::string, std::vector<std::function<void(const int&)>>> eventsInt;

	EventHandler() = default;
	virtual ~EventHandler() = default;

	EventHandler(const EventHandler& other) = delete;
	EventHandler& operator=(const EventHandler& other) = delete;

public:
	void AddEvent(const std::string& id, std::function<void()>action);
	void AddEventGo(const std::string& id, std::function<void(const GameObject&)>action);
	void AddEventInt(const std::string& id, std::function<void(const int&)>action);
	void DeleteEvent(const std::string& id);
	void InvokeEvent(const std::string& id);
	void InvokeEvent(const std::string& id, const GameObject& go);
	void InvokeEvent(const std::string& id, const int& num);
};

#define EVENT_HANDLER (EventHandler::Instance())