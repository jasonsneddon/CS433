/*
* des.cpp
* This is the des class used to run the various scheduling
* algorithms.
*
*/
#include <queue>
#include <iostream>
#include <cstdlib>

#include "event.h"
#include "scheduler.h"
#include "random.h"

using namespace std;


priority_queue<Event, vector<Event>, Event::Comparator> eventQueue;

void addEvent(Event eve)
{
	eventQueue.emplace(eve);
}

int main()
{
	scheduler s;
	process p;
      p.printHeader();

	// The maximum time for all processes to run on CPU is 300 seconds
	int quitTime = 30000;

	// Number of processes is specified by a parameter on the command line
	int numOfProcesses;
	cout << "How many processes? " << endl;
	cin >> numOfProcesses;

	// Ask user what scheduling algorithm to run
	int pickAlgorithm;
	cout << "Which scheduling algorithm would you like to run? " << endl;
	cout << "\t Enter 1 for First Come, First Served " << endl;
	cout << "\t Enter 2 for Shortest Job First " << endl;
	cin >> pickAlgorithm;

	if (pickAlgorithm == 1)
	{
		cout << "Running First Come, First Served scheduling algorithm..." << endl;
		queue<Event> rQueue;

	}
	else
	{
		cout << "Running Shortest Job First scheduling algorithm..." << endl;
		//priority_queue<Event> rQueue;

	}

	// Initialize event queue and add all process arrival events
	// with the right time stamps
	//std::priority_queue<Event, std::vector<Event>, Event::Comparator> eventQueue;
	for (int i = 0; i < numOfProcesses; i++)
	{
		Event arrEvent;
		eventType arrType = PROCESS_ARRIVAL;
		arrEvent.processID = i;
		arrEvent.time = ranInt(0, 30000);
		arrEvent.setType(arrType);
		eventQueue.emplace(arrEvent);
	}

	// Initialize the current time
	int currentTime = 0;

	// While loop
	while (!eventQueue.empty() && currentTime < quitTime)
	{

		// Get the next event from the eventQueue
		Event e = eventQueue.top();
		eventQueue.pop();

		//update currentTime
		currentTime = e.time;

		//handle the event
		e.setEventQueue(eventQueue);

		e.handleTheEvent(e);
		eventQueue = e.getEventQueue();

		p.setProcessID(e.processID);
		p.printStats();

	}


//	system("PAUSE");
//	return 0;
} // end main




  // End des_Simulation class


