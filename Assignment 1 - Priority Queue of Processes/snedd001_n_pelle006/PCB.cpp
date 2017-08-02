#include "PCB.h"
#include <iostream>
using namespace std;

PCB::PCB()
{}

PCB::PCB(int id, int prior)
{
	PCB_ID = id;
	priority = prior;
	currentState = NEW;
}

PCB::~PCB()
{}

void PCB::printHeader()
{
	cout << "====================================================" << endl;
	cout << "Authors      : Pierre Pelletier and Jason Sneddon" << endl;
	cout << "Course       : CS433 - Operating Systems" << endl;
	cout << "Assignment   : Priority Queue of Processes" << endl;
	cout << "Date         : 09/19/2016" << endl;
	cout << "====================================================\n" << endl;
}

void PCB::setPCB_ID(int ID)
{
	PCB_ID = ID;
}

int PCB::getPCB_ID()
{
	return PCB_ID;
}

void PCB::setPriority(int prior)
{
	priority = prior;
}

int PCB::getPriority()
{
	return priority;
}

void PCB::setCurrentState(ProcessState state)
{
	currentState = state;
}

ProcessState PCB::getCurrentState()
{
	return currentState;
}

ostream& operator<<(ostream& os, PCB& PCBout)
{
	if (PCBout.getPCB_ID() == 1)
	{
		PCBout.setPCB_ID(2);
	}
	if (PCBout.getPriority() == 1)
	{
		PCBout.setPriority(2);
	}
	os << "  \nPID: " << PCBout.getPCB_ID() - 1 << " " << "Priority: " << PCBout.getPriority() - 1;
	return os;
}
