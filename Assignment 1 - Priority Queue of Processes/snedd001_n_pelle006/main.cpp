#include "PCB.h"
#include "PCB_Table.h"
#include "ReadyQueue.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
	//create PCB object in order to print out the header
	PCB header;
	header.printHeader();


	//TEST !

	//create table of 20 entries
	PCB_Table table;
	table.createTable(20);

	//create a ReadyQueue q1, get PCB's from table and insert them into q1
	ReadyQueue q1;
	q1.insertProc(table.getElementFromTable(5));
	q1.insertProc(table.getElementFromTable(1));
	q1.insertProc(table.getElementFromTable(8));
	q1.insertProc(table.getElementFromTable(11));

	//use these functions for removing highest priority process from queue
	//and to display the remaining elements in the queue
	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.insertProc(table.getElementFromTable(3));
	q1.insertProc(table.getElementFromTable(7));
	q1.insertProc(table.getElementFromTable(2));
	q1.insertProc(table.getElementFromTable(12));
	q1.insertProc(table.getElementFromTable(9));

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	q1.removeHighestProc();
	q1.displayQueue();

	//TEST 2

	srand(time(0));

	for (int i = 1; i <= 10; i++)
	{
		int randIndex = rand() % 19;
		PCB randElement;
		randElement = table.getElementFromTable(randIndex);
		randElement.setPriority(rand() % 50 + 1);
		q1.insertProc(randElement);
		if (q1.size() < i)
		{
			i -= 1;
		}
	}

	for (int k = 0; k < 1000000; k++)
	{
		q1.removeHighestProc();

		for (unsigned int j = 0; j < 9; j++)
		{
			q1.aging(j);
		}

		while (q1.size() < 10)
		{
			int randIndex3 = rand() % 19;
			PCB randElement3;
			randElement3 = table.getElementFromTable(randIndex3);
			randElement3.setPriority(rand() % 50 + 1);
			q1.insertProc(randElement3);
		}
	}
	q1.reHeap();
	q1.displayQueue();

	system("PAUSE");
	return 0;
}
