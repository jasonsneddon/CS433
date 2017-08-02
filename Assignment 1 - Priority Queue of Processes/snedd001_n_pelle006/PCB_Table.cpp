#include "PCB_Table.h"
#include <iostream>
using namespace std;

PCB_Table::PCB_Table()
{

}

PCB_Table::~PCB_Table()
{

}

void PCB_Table::createTable(int numberOfEntries)
{
	for (int i = 1; i <= numberOfEntries ; i++)
	{
		PCB newProcess = PCB(i, i);
		vectorOfProcesses.push_back(newProcess);
	}
}

PCB PCB_Table::getElementFromTable(int id)
{
	return vectorOfProcesses.at(id);
}
