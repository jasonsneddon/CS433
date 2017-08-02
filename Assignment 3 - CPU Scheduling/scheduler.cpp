/*
* scheduler.cpp
* This is the scheduler class used for handling the different
* type of events. The scheduler selects a process from the
* Ready Queue to run.
*
*/

#include <iostream>
#include "scheduler.h"
#include "Event.h"
#include "process.h"
#include "random.h"
#include <queue>

using namespace std;

// Constructor
scheduler::scheduler()
{

}

//Destructor
scheduler::~scheduler()
{

}

void scheduler::setEventQueue(std::priority_queue<Event, std::vector<Event>, Event::Comparator> eQueue)
{
	eveQueue = eQueue;
}

std::priority_queue<Event, std::vector<Event>, Event::Comparator> scheduler::getEventQueue()
{
	return eveQueue;
}

// Function to handle process arrival
// PARAM: takes an event object
void scheduler::handleProcessArrival(Event e)
{

	proc.setProcessID(e.processID);

	// Generate the length of next CPU burst
	proc.setAverageCPUBurst();
	proc.setNextCPUBurst();

	proc.setStartTime(e.time);
	proc.setTotalCPUDuration();

	proc.setRemainingCPUDuration();

	// Add process to the readyQueue
	readyQueue.push(proc);
	proc.status = READY;

	// Schedule new event
	scheduleEvent();


}

void scheduler::handleCPUCompletion(Event e)
{
      //proc.setProcessID(e.processID);
      //proc.setRemainingCPUDuration();
      //proc.updateRemainingTime();
      if(proc.getRemainingCPUDuration() <= 0)
      {
            if (readyQueue.empty())
            {
                  proc.printStats();
                  return;
            }
            else
            {
                  readyQueue.pop();
                  proc.printStats();
            }
      }
      else
      {
            // Generate a random IO burst length
            proc.setIOBurstTime();

            // Create an IO completion event
            Event IOCompletion;

            IOCompletion.type = IO_COMPLETION;

            // Add the new event into the eventQueue
            eveQueue.push(IOCompletion);
  }

  // Change CPU state to idle
  CPUState = false;

  // Schedule next Event
  scheduleEvent();


}

void scheduler::handleIOCompletion(Event e)
{
      //process proc;
      proc.setProcessID(e.processID);

      // Generate the length of the next CPU burst
      proc.setNextCPUBurst();

      proc.updateRemainingTime();

      // Add the process to the readyQueue
      readyQueue.push(proc);

      // Schedule new Event
      scheduleEvent();
}

void scheduler::handleTimerExpiration(Event e)
{

	//process proc;
	proc.setProcessID(e.processID);

	// Move running process to the readyQueue
	readyQueue.push(proc);
	// Update the moved process CPU burst length
	proc.setRemainingCPUDuration();
	// Change moved process state to idle;
	proc.processState = false;
	// Schedule new Event
	scheduleEvent();


}

void scheduler::scheduleEvent()
{

	if (CPUState == false)
	{
		if (readyQueue.empty())
		{
			return;
		}
		else
		{
			// Select and dispatch a process from the readyQueue
			proc = readyQueue.front();
			proc.status = RUNNING;
			readyQueue.pop();

			CPUState = true;

			// Create a CPU completion event
			Event CPUcompletion;
			CPUcompletion.setTime(proc.getRemainingCPUDuration());
			CPUcompletion.processID = proc.getProcessID();
			CPUcompletion.type = CPU_BURST_COMPLETION;
			// Add the new event to eventQueue

			eveQueue.emplace(CPUcompletion);
			//CPUcompletion.handleTheEvent(CPUcompletion, eQueue);
		}
	}
}
