// SCHEDULER_H
/*
* scheduler.h
* This is the header file for the scheduler class.
*
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

//#include <queue>
#include "process.h"
#include "Event.h"


class scheduler
{
public:

	process proc;

	bool CPUState;

	//Function prototypes
	scheduler();
	~scheduler();

	std::priority_queue<Event, std::vector<Event>, Event::Comparator> eveQueue;

	void setEventQueue(std::priority_queue<Event, std::vector<Event>, Event::Comparator> eQueue);
	std::priority_queue<Event, std::vector<Event>, Event::Comparator> getEventQueue();

	void handleProcessArrival(Event e);
	void handleCPUCompletion(Event e);
	void handleIOCompletion(Event e);
	void handleTimerExpiration(Event e);

	void scheduleEvent();

	std::queue<process> readyQueue;

private:
};


#endif

