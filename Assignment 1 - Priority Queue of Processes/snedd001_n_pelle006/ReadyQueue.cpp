#include "ReadyQueue.h"
#include "PCB.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <time.h>
using namespace std;

ReadyQueue::ReadyQueue()
{}
ReadyQueue::~ReadyQueue()
{}

int ReadyQueue::size()
{
	return heap.size();
}

void ReadyQueue::insertProc(PCB element)
{
	for (unsigned int c = 0; c < heap.size(); c++)
	{
		if (element.getPCB_ID() == heap[c].getPCB_ID())
		{
			return;
		}
	}
	element.setCurrentState(READY);
	heap.push_back(element);
	heapifyUp(heap.size() - 1);
}

void ReadyQueue::deleteMin()
{
	//check to see if heap is empty
	if (heap.size() == 0)
	{
		return;
	}
	//delete minimum element
	heap[0].setCurrentState(RUNNING);
	heap[0] = heap.at(heap.size() - 1);
	heap.pop_back();
	heapifyDown(0);
}

void ReadyQueue::removeHighestProc()
{
	//check to see if heap is empty
	if (heap.size() == 0)
	{
		return;
	}
	else
	{
		deleteMin();
	}
}

void ReadyQueue::heapifyUp(int index)
{
	if (index >= 0 && parent(index) >= 0 && heap[parent(index)].getPriority() > heap[index].getPriority())
	{
		PCB temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		heapifyUp(index);
	}
}

void ReadyQueue::heapifyDown(int index)
{
	int childL = left(index);
	int childR = right(index);
	if (childL >= 0 && childR >= 0 && heap[childL].getPriority() > heap[childR].getPriority())
	{
		childL = childR;
	}
	if (childL > 0 && childR >= 0)
	{
		PCB temp = heap[index];
		heap[index] = heap[childL];
		heap[childL] = temp;
		heapifyDown(childL);
	}
}
int ReadyQueue::left(int parent)
{
	unsigned int l = 2 * parent + 1;
	if (l < heap.size())
		return l;
	else
		return -1;
}

/*
* Return Right Child
*/
int ReadyQueue::right(int parent)
{
	unsigned int r = 2 * parent + 2;
	if (r < heap.size())
		return r;
	else
		return 0;
}

/*
* Return Parent
*/
int ReadyQueue::parent(int child)
{
	int p = (child - 1) / 2;
	if (child == 0)
		return 0;
	else
		return p;
}

void ReadyQueue::displayQueue()
{
	vector <PCB>::iterator pos = heap.begin();
	cout << "\nQueue:  ";

	while (pos != heap.end())
	{
		cout << *pos << " ";
		pos++;
	}
	cout << endl;
}

void ReadyQueue::aging(unsigned int index)
{
	if(index < heap.size())
	{
		if(heap[index].getPriority() == 1)
		{
			return;
		}
		else
		{
			heap[index].setPriority(heap[index].getPriority() - 1);
		}
	}
}

void ReadyQueue::reHeap()
{
	for (int i = heap.size() - 1; i >= 0; i--)
	{
		heapifyUp(i);
	}
}
