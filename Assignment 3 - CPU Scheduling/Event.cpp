/*
* event.cpp
* This is the event class used to construct and event
*
*/

#include <queue>
#include <iostream>
#include "Event.h"
#include "scheduler.h"

using namespace std;

scheduler s;

//Constructor
Event::Event()
{

}

//Destructor
Event::~Event()
{

}

void Event::setEventQueue(std::priority_queue<Event, std::vector<Event>, Event::Comparator> eQueue)
{
	eveQueue = eQueue;
}

std::priority_queue<Event, std::vector<Event>, Event::Comparator> Event::getEventQueue()
{
	return eveQueue;
}

void Event::setTime(int t)
{
	time = t;
}

int Event::getTime()
{
	return time;
}

void Event::setType(eventType t)
{
	type = t;
}
eventType Event::getType()
{
	return type;
}

// Function to handle the type of events
void Event::handleTheEvent(Event e)
{
	//scheduler s;

	switch (e.type)
	{
	case PROCESS_ARRIVAL:
		s.setEventQueue(eveQueue);
		s.handleProcessArrival(e);
		eveQueue = s.getEventQueue();
		break;
	case CPU_BURST_COMPLETION:
		s.setEventQueue(eveQueue);
		s.handleCPUCompletion(e);
		eveQueue = s.getEventQueue();
		break;
	case IO_COMPLETION:
		s.setEventQueue(eveQueue);
		s.handleIOCompletion(e);
		eveQueue = s.getEventQueue();
		break;
	case TIMER_EXPIRATION:
		s.setEventQueue(eveQueue);
		s.handleTimerExpiration(e);
		eveQueue = s.getEventQueue();
		break;
	default:
		break;

	}

}


// end class event.cpp


