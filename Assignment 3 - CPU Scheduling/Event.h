// EVENT_H
/*
* event.h
* This is the header file for the event class.
*
*/

#ifndef EVENT_H
#define EVENT_H

#include <queue>
//#include "scheduler.h"

// Type of event
enum eventType
{
	PROCESS_ARRIVAL = 1,
	CPU_BURST_COMPLETION,
	IO_COMPLETION,
	TIMER_EXPIRATION
};

class Event
{
public:
	Event();
	~Event();

	class Comparator
	{
	public:
		bool operator() (const Event& e1, const Event& e2)
		{
			return e1.time > e2.time;
		}
	};

	std::priority_queue<Event, std::vector<Event>, Event::Comparator> eveQueue;

	void setEventQueue(std::priority_queue<Event, std::vector<Event>, Event::Comparator> eQueue);
	std::priority_queue<Event, std::vector<Event>, Event::Comparator> getEventQueue();

	void handleTheEvent(Event e);

	// Time when the event is scheduled to occur
	int time;
	// Process to which the event belongs to
	int processID;
	// Type of event
	eventType type;

	void setTime(int t);
	int getTime();

	void setType(eventType t);
	eventType getType();

private:
};

#endif

