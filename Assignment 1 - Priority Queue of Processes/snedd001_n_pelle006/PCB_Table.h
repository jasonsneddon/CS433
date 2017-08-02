#ifndef PCB_TABLE_H
#define PCB_TABLE_H

#include "PCB.h"
#include "vector"
class PCB_Table : public PCB
{
private:
	std::vector<PCB> vectorOfProcesses;
public:
	PCB_Table();
	~PCB_Table();
	void createTable(int numberOfEntries);
	PCB getElementFromTable(int id);
};
#endif
