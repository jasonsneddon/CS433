#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

// Function prototypes
void randomReplace(int, int);
void FIFO(int, int);
void LRU(int, int);
void printHeader();


/*
 * PURPOSE: Runs the Random, FIFO, and LRU Page Replacement simulations.
 * @PARAMS:
 *   int argc - the number of parameters being passed from the command line
 *   char *argv[] - contains the 3 parameters being passed from command line:
 *      0. File name.
 *      1. Page Size - Power of 2 between 256 and 8192.
 *      2. Physical Memory Size - Number of address bits (4MB, 16MB, 32MB, 64MB).
 */
int main(int argc, char *argv[])
{
     // Verify that a valid number of arguments were entered in command line
	if (argc != 3)
	{
		cout << "Invalid number of arguments.\n" << endl;
		return 0;
	}
	else
	{
          // Display header
		printHeader();

		// Store command line arguments: page size and physical memory size
		int pageSize = atoi(argv[1]);
		int physMemSize = atoi(argv[2]);

          /*
           * Random Page Replacement Simulation:
           *   - Initialize start time
           *   - Run Random Replacement Simulation
           *   - Get end time
           *   - Calculate elapsed time
           */
		time_t randomStart = time(0);
		randomReplace(pageSize, physMemSize);
		time_t randomEnd = time(0);
		double randomTime = difftime(randomEnd, randomStart);
		cout << "Elapsed time: " << randomTime << "s" << endl << endl;

          /*
           * FIFO Page Replacement Simulation:
           *   - Initialize start time
           *   - Run FIFO Replacement Simulation
           *   - Get end time
           *   - Calculate elapsed time
           */
		time_t FIFOStart = time(0);
		FIFO(pageSize, physMemSize);
		time_t FIFOEnd = time(0);
		double FIFOTime = difftime(FIFOEnd, FIFOStart);
		cout << "Elapsed time: " << FIFOTime << "s" << endl << endl;

		/*
		 * Run LRU Page Replacement Simulation
		 */
		LRU(pageSize, physMemSize);
	}
	return 0;
} // End main
//=======================    FUNCTIONS   =======================
/*
 * PURPOSE: Function to implement the Random Page Replacement Algorithm.
 *          This simply replaces a random page in memory.
 */

void randomReplace(int pgSize, int memSize)
{
     // Initialize memory references, page faults, and flushes
	int memoryReferences = 0;
	int pageFaults = 0;
	int flushes = 0;

	// Calculate the number of frames based on the page and
	// physical memory size
	int numOfFrames = memSize * 1048576 / pgSize;


	// Create and populate page table
	const int rows = 134217728 / pgSize;
	const int columns = 3;
	int **pageTable = new int *[rows];

	for(int k = 0; k < rows; k++)
	{
		pageTable[k] = new int[columns];
	}

     // List of free frames; initially, all frames are free
	list <int> freeFramesList;

	for(int i = 0; i < numOfFrames; i++)
	{
		freeFramesList.push_back(i);
	}

	// Object to read addresses from file
	ifstream inFile("References.txt");

	int pageNumber;
	string address;
	int addr;
	int victim;

     // Read virtual memory addresses from file line by line
	while (getline(inFile, address))
	{
		memoryReferences++;

		// Calculate the page number
		pageNumber = atoi(address.c_str()) / pgSize;

		addr = atoi(address.c_str());

		// If LSB is write access, set Dirty
		if (addr % 2 != 0)
		{
			pageTable[pageNumber - 1][2] = 1;
		}
		else
		{
               // Read access, set Not Dirty
			pageTable[pageNumber - 1][2] = 0;
		}

		/* Check to see if there are any free frames, if there
		 * is a free frame, use it.
		 */
		if (!freeFramesList.empty())
		{
			if (pageTable[pageNumber - 1][1] == 0)
			{
				pageTable[pageNumber - 1][0] = freeFramesList.front();
				freeFramesList.pop_front();
				pageTable[pageNumber - 1][1] = 1;
				pageFaults++;
			}
		}
		/* Free frames list is empty (no free frames) so we have to flush
		 * some other page first.
		 *   - If the other page is clean, throw it away.
		 *   - If the other page is dirty, then write it out before reusing
		 *     its frame.
		 */
		else
		{
               // Main memory full so select a random victim page to evict
			if (pageTable[pageNumber - 1][1] == 0)
			{
				do
				{
					victim = rand() % (rows - 1);
				} while (pageTable[victim][1] != 1);

				pageTable[victim][1] = 0;

				// Flush page to free frame
				if (pageTable[victim][2] == 1)
				{
					flushes++;
				}

				// Update the page table
				pageTable[pageNumber - 1][1] = 1;
				pageFaults++;
			}
		}

	}

	// Close file and print statistics for algorithm
	inFile.close();
	cout << "RANDOM REPLACEMENT:" << endl;
	cout << "Number of memory references: " << memoryReferences << endl;
	cout << "Number of page faults: " << pageFaults << endl;
	cout << "Number of flushes: " << flushes << endl;
}

/*
 * PURPOSE: Function to implement the FIFO Page Replacement Algorithm.
 *          The FIFO algorithm simply flushes the page that has been there
 *          the longest duration, ignoring the usage of the page.
 */
void FIFO(int pgSize, int memSize)
{
     // Initialize memory references, page faults, and flushes
	int memoryReferences = 0;
	int pageFaults = 0;
	int flushes = 0;

	// Calculate number of frames
	int numOfFrames = memSize * 1048576 / pgSize;

     // Create page table
	const int rows = 134217728 / pgSize;
	const int columns = 3;
	int **pageTable = new int *[rows];

	for(int k = 0; k < rows; k++)
	{
		pageTable[k] = new int[columns];
	}

     // Create and populate inital free frame list
	list <int> freeFramesList;
	for(int i = 0; i < numOfFrames; i++)
	{
          freeFramesList.push_back(i);
	}

     // Open file to read virtual addresses
	ifstream inFile("References.txt");

	int pageNumber;
	string address;
	int addr;
	int victim;
	int victimFrame = 0;

	// Read virtual memory addresses line by line
	while (getline(inFile, address))
	{
		memoryReferences++;

          // Calculate the page number
		pageNumber = atoi(address.c_str()) / pgSize;
		addr = atoi(address.c_str());

		// Check to see if virtual addresss is read or write
		if (addr % 2 != 0)
		{
			pageTable[pageNumber - 1][2] = 1;
		}
		else
		{
			pageTable[pageNumber - 1][2] = 0;
		}

		// If there's a free frame, use it
		if (!freeFramesList.empty())
		{
			if (pageTable[pageNumber - 1][1] == 0)
			{
				pageTable[pageNumber - 1][0] = freeFramesList.front();
				freeFramesList.pop_front();
				pageTable[pageNumber - 1][1] = 1;
				pageFaults++;
			}
		}
          /* Free frames list is empty (no free frames) so we have to flush
		 * some other page first.
		 *   - If the other page is clean, throw it away.
		 *   - If the other page is dirty, then write it out before reusing
		 *     its frame.
		 */
		else
		{
			int j;
               // Page is read(0) so flush it
			if(pageTable[pageNumber - 1][1] == 0)
			{
                    // Check if victim is last
				if(victimFrame == numOfFrames)
				{
					victimFrame = 0;
					for(j = 0; j < rows; j++)
					{
						if(pageTable[j][0] == victimFrame && pageTable[j][1] == 1)
						{
							victim = j;
							break;
						}
					}
					pageTable[pageNumber - 1][0] = victimFrame;
					pageTable[pageNumber - 1][1] = 1;
					pageTable[victim][1] = 0;
					if (pageTable[victim][2] == 1)
					{
						flushes++;
					}
				}
				// Victim is not last
				else
				{
					for(j = 0; j < rows; j++)
					{
						if (pageTable[j][0] == victimFrame && pageTable[j][1] == 1)
						{
							victim = j;
							break;
						}
					}
					pageTable[pageNumber - 1][0] = victimFrame;
					pageTable[pageNumber - 1][1] = 1;
					pageTable[victim][1] = 0;
					if (pageTable[victim][2] == 1)
					{
						flushes++;
					}
					victimFrame++;
				}
				pageFaults++;
			}
		}
	}

     // Close file and print statistics for algorithm
	inFile.close();
	cout << "FIRST-IN FIRST-OUT REPLACEMENT:" << endl;
	cout << "Number of memory references: " << memoryReferences << endl;
	cout << "Number of page faults: " << pageFaults << endl;
	cout << "Number of flushes: " << flushes << endl;
}


/*
 * PURPOSE: Function to implement the LRU Page Replacement Algorithm.
 *          The LRU algorithm flushes the page that has not been used
 *          in the most amount of time.
 *
 */
void LRU(int pgSize, int memSize)
{
     // Initialize start time and variables
	time_t LRUStart = time(0);
	int memoryReferences = 0;
	int pageFaults = 0;
	int flushes = 0;

	// Calculate the number of frames
	int numOfFrames = memSize * 1048576 / pgSize;

     // Create page table
	const int rows = 134217728 / pgSize;
	const int columns = 4;
	int **pageTable = new int *[rows];

	for(int k = 0; k < rows; k++)
	{
		pageTable[k] = new int[columns];
	}

	// Create a list of free frames
	list <int> freeFramesList;
     // Initially, all frames are empty
	for(int i = 0; i < numOfFrames; i++)
	{
		freeFramesList.push_back(i);
	}

	// Open file for virtual addresses
	ifstream inFile("References.txt");

	int pageNumber;
	string address;
	int addr;
	int victim;

	// Counter to keep track of how frequently a page has been used
	int counter;

	clock_t clkStart = clock();

     // Read virtual addresses from file
	while (getline(inFile, address))
	{
		memoryReferences++;

		// At each clock cycle, if a page has been used, increment its counter
		clock_t clkCheck = clock();
		double counter = (double)(clkCheck - clkStart) / CLOCKS_PER_SEC * 1000;

		// Get page number
		pageNumber = atoi(address.c_str()) / pgSize;
		pageTable[pageNumber][3] = counter;

          // Check to see if virtual addresss is read(0) or write(1)
		addr = atoi(address.c_str());
		if(addr % 2 != 0)
		{
			pageTable[pageNumber - 1][2] = 1;
		}
		else
		{
			pageTable[pageNumber - 1][2] = 0;
		}
          // If there's a free frame, use it
		if(!freeFramesList.empty())
		{
			if (pageTable[pageNumber - 1][1] == 0)
			{
				pageTable[pageNumber - 1][0] = freeFramesList.front();
				freeFramesList.pop_front();
				pageTable[pageNumber - 1][1] = 1;
				pageFaults++;
			}
		}
		else
		{
               // No free frames
			if (pageTable[pageNumber - 1][1] == 0)
			{
				int l;

				// Find the least recently used page
				double cnt = pageTable[pageNumber][3];
				for(l = 0; l < rows; l++)
				{
					if (pageTable[l][3] < cnt && pageTable[l][1] == 1)
					{
						cnt = pageTable[l][3];
						victim = l;
					}
				}

                    // Flush page and update page table and stats
				pageTable[victim][1] = 0;
				pageTable[pageNumber - 1][1] = 1;
				if (pageTable[victim][2] == 1)
				{
					flushes++;
				}
				pageFaults++;
			}
		}
	}

	// Close file
	inFile.close();

	// Calculate elapsed time and display stats
	time_t LRUEnd = time(0);
	double LRUTime = difftime(LRUEnd, LRUStart);
	cout << "LEAST RECENTLY USED REPLACEMENT:" << endl;
	cout << "Number of memory references: " << memoryReferences << endl;
	cout << "Number of page faults: " << pageFaults << endl;
	cout << "Number of flushes: " << flushes << endl;
	cout << "Elapsed time: " << LRUTime << "s" << endl << endl;
}



/*
 * PURPOSE: Displays the header before running the page replacement algorithms
 *
 */
void printHeader()
{
     cout << "\n===========================================================" << endl;;
	cout << "Authors         : Pierre Pelletier and Jason Sneddon" << endl;
	cout << "Course          : CS433 - Operating Systems" << endl;
	cout << "Assignment 4    : Simulation of Page Replacement Algorithms " << endl;
	cout << "Date            : December 9, 2016" << endl;
	cout << "===========================================================\n\n" << endl;
}

//===========================     END FILE     =========================================
