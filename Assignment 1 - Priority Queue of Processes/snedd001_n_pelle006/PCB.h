#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <fstream>

using namespace std;

enum ProcessState
{
	NEW = 1,
	READY = 2,
	RUNNING = 3,
	WAITING = 4,
	TERMINATED = 5
};

class PCB
{
private:
	int PCB_ID;
	int priority;
	ProcessState currentState;

public:
	PCB();
	PCB(int id, int prior);
	~PCB();
	void printHeader();
	void setPCB_ID(int ID);
	int getPCB_ID();
	void setPriority(int p);
	int getPriority();
	void setCurrentState(ProcessState state);
	ProcessState getCurrentState();
	friend ostream& operator<<(ostream& os, PCB& PCBout);
};

#endif
