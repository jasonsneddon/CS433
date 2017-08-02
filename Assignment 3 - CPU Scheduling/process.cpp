/*
* CLASS: process.cpp
*
* PURPOSE: This class is used to simulate a process. When a
*          process is ready to run, it is added to the Ready
*          Queue. For this simulation, a process will have
*          an alternating sequence of CPU Bursts and I/O
*          operations. The total number of processes to be
*          included in the simulation is provided as the
*          first command line argument.
*
*          A process contains:
*              a Process ID, start time, Total CPU duration,
*              Remaining CPU duration, Average CPU burst length,
*              Next CPU burst length, I/O burst time,
*              priority, and status.
*/

#include "process.h"
#include "random.h"
#include "Event.h"

#include <iostream>
#include <string>
using namespace std;

/*
* PURPOSE: Constructs a process object.
*/
process::process()
{


}

process::~process()
{

}

void process::setProcessID(int id)
{
	processID = id;
}

int process::getProcessID()
{
	return processID;
}

/*
* PURPOSE: Generates a start time for a process that is randomly
*                  distributed from 0 to 5 minutes.
*/
void process::setStartTime(int t)
{
	startTime = t;
}
/*
* PURPOSE: Returns the start time of a process.
*/
int process::getStartTime()
{
	return startTime;
}


/*
* PURPOSE: Set average CPU burst time. This is determined
*          when a process is initially created and is
*          between 5ms and 100ms. This is used to determine
*          the length of the next CPU burst.
*/
void process::setAverageCPUBurst()
{
	averageCPUBurst = ranInt(5, 100);
}

/*
* PURPOSE: Returns the value for averageCPUBurst
*/
int process::getAverageCPUBurst()
{
	return averageCPUBurst;
}

/*
* PURPOSE: Sets the value of nextCPUBurst. This is randomly
*          determined based on averageCPUBurst, and is generated
*          when a process is moved into the ready queue.
*/
void process::setNextCPUBurst()
{
	nextCPUBurst = CPUBurstRandom(getAverageCPUBurst());
}

/*
* PURPOSE: Returns the value of nextCPUBurst
*/
int process::getNextCPUBurst()
{
	return nextCPUBurst;
}

/*
* PURPOSE: Set the total CPU Burst time, does not include wait time
*          The nextCPUBurst is the length of time the process runs
*          on the CPU.
*/
void process::setTotalCPUDuration()
{
	totalCPUDuration = ranInt(100, 6000);
}

/*
* PURPOSE: Returns the total CPU burst time, called totalCPUDuration
*/
int process::getTotalCPUDuration()
{
	return totalCPUDuration;
}

/*
* PURPOSE: Set the remaining CPU burst time. When a process completes
*          its CPU Burst, the burst time is subtracted from the remaining
*          CPU duration. When this is zero, a process terminates.
* PARAM:   CPUBurstTime is nextCPUBurst, which is the amount of time a
*          process runs on the CPU.
*/
void process::setRemainingCPUDuration()
{
	remainingCPUDuration = totalCPUDuration - nextCPUBurst;
}

void process::updateRemainingTime()
{
	remainingCPUDuration = remainingCPUDuration - nextCPUBurst;
}

/*
* PURPOSE: Returns the remaining CPU burst time, called remainingCPUDuration
*/
int process::getRemainingCPUDuration()
{
	return remainingCPUDuration;
}

/*
* PURPOSE: Sets IO burst time to a randomly generated number between 30ms
*          and 100ms. This is generated when each process completes a CPU
*          burst and moves to the I/O queue.
*/
void process::setIOBurstTime()
{
	IOBurstTime = ranInt(30, 100);
}

/*
* PURPOSE: Returns the value of IOBurstTime.
*/
int process::getIOBurstTime()
{
	return IOBurstTime;
}

/*
* PURPOSE: Displays the statistics for a given process
*
*/
void process::printStats()
{
	cout << "Process: " << processID << endl;
	cout << "Arrival Time: " << getStartTime() / 100 << endl;
	cout << "Finish Time: " << (getStartTime() + totalCPUDuration) / 100 << endl;
	cout << "Service Time: " << endl;
	cout << "I/O Time: " << endl;
	cout << "Turnaround Time: " << endl;
	cout << "Waiting Time: " << endl << endl;
}

/*
 * PURPOSE: Displays header before simulation begins
 */
void process::printHeader()
{
    cout << "====================================================" << endl;
	cout << "Authors      : Pierre Pelletier and Jason Sneddon" << endl;
	cout << "Course       : CS433 - Operating Systems" << endl;
	cout << "Assignment   : Discrete Event Simulation" << endl;
	cout << "Date         : November 2, 2016" << endl;
	cout << "====================================================\n" << endl;
}


//---------- END PROCESS CLASS ----------
