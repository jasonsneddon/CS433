/*
* CLASS: process.h
*
* PURPOSE: This is the header file for the process class.
*          A process contains:
*              a Process ID, start time, Total CPU duration,
*              Remaining CPU duration, Average CPU burst length,
*              Next CPU burst length, I/O burst time,
*              priority, and status.
*/

#ifndef PROCESS_H
#define PROCESS_H

// Represents the current status of a process
enum ProcessStatus {
	READY = 0,
	RUNNING,
	WAITING,
	TERMINATED
};

class process
{
public:
	// Variables
	int processID;
	int startTime;
	int totalCPUDuration;
	int remainingCPUDuration;
	int averageCPUBurst;
	int nextCPUBurst;
	int IOBurstTime;

	/* Integer representing the priority of a process.
	* A low number is a high priority and a high number
	* is a low priority. This is used by the scheduler
	* to decide which process will be running next.
	*/
	int priority;

	/* Represents the status of a process. A process can
	*      be: Ready, Running, Waiting, or Terminated.
	*/
	ProcessStatus status;

	/* Represents the state of a process.
	* 0 indicates Idle
	* 1 indicates Busy
	*/
	bool processState;

	// Functions
	process();
	~process();

	void setStartTime(int t);
	int getStartTime();

	void setProcessID(int id);
	int getProcessID();

	void setAverageCPUBurst();
	int getAverageCPUBurst();

	void setNextCPUBurst();
	int getNextCPUBurst();

	void setTotalCPUDuration();
	int getTotalCPUDuration();

	void setRemainingCPUDuration();
	int getRemainingCPUDuration();

	void updateRemainingTime();

	void setIOBurstTime();
	int getIOBurstTime();

	void printStats();
      void printHeader();

private:
};

#endif

