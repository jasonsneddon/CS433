#include <stdio.h>
#include <stdlib.h>
#include <time.h>        // Required for time()
#include <unistd.h>      // Required for sleep()
#include <pthread.h>     // Required for pthreads
#include <semaphore.h>   // Required for semaphores

#include "buffer.h"

#define TRUE 1

// Function prototypes
/*
 * PURPOSE: Displays the header before running the producer-consumer
 *                  simulation.
 */
void print_header();
/*
 * PURPOSE: Function to initialize the mutual exclusion
 *          object mutex, along with the empty and full
 *          semaphores.
 */
void initialize();
/*
 * PURPOSE: Returns a random number between 1 and 1000
 */
int randomNumber();
/*
 * PURPOSE: Displays the content of the shared buffer
 * @PARAMS: integer
 */
void displayBuffer(int c);
/*
 * PURPOSE: Buffer operation used by the Producer thread
 *          to insert an item into the buffer.
 * @PARAMS: buffer_item
 *
 * RETURNS:
 *    - 0 if successful
 *    - Otherwise -1 indicating an error
 */
int insert_item(buffer_item item);
/*
 * PURPOSE: Buffer operation used by the Consumer thread to
 *          remove an item from the buffer.
 * @PARAMS: buffer_item
 * RETURNS: returns 0 if succesful. returns -1 if not.
 */
int remove_item(buffer_item *item);
/*
 * PURPOSE: The Producer thread will alternate between sleeping for
 *                  a random period of time and inserting a random integer
 *                  into the buffer.
 */
void *producer(void *param);
/*
 * PURPOSE: The Consumer will also sleep for a random period of time
 *                  and, upon awakening, the consumer will attempt to
 *                  remove an item from the buffer.
 *
 */
void *consumer(void *param);

// Global variables
buffer_item buffer[BUFFER_SIZE];    // Buffer of size 5

sem_t empty;                                  // For acquiring the empty lock
sem_t full;                                       // For acquiring the full lock
pthread_mutex_t mutex;                 // Mutex lock for critical section

pthread_t pTID;                                // Producer thread id
pthread_t cTID;                                // Consumer thread id
pthread_attr_t attr;                          // Thread attributes

int count;                                         // Counter to keep track of the number of items in the buffer
int mainSleep;                                  // Main thread sleep time
int itemCount;                                  // Keeps track of the last element in the buffer


/*
 * PURPOSE: Runs the Producer-Consumer simulation.
 * @PARAMS:
 *   int argc - the number of parameters being passed from the command line
 *   char *argv[] - contains the 4 parameters being passed from command line:
 *      0. File name.
 *      1. How long the main thread sleep before terminating.
 *      2. The number of producer threads.
 *      3. The number of consumer threads.
 */
int main(int argc, char *argv[])
{
      // Check validity of command line arguments
      if(argc != 4)
      {
            printf("Error: Not enough arguments were entered.\n");
            return -1;
      }
      if(atoi(argv[1]) < 0 || atoi(argv[2]) < 0 || atoi(argv[3]) < 0)
      {
            printf("Error: Entries must be greater than or equal to 0");
            return -1;
      }

      // Store arguments
      mainSleep = atoi(argv[1]);
      int producerThreadsToCreate = atoi(argv[2]);
      int consumerThreadsToCreate = atoi(argv[3]);

      // Print header
      print_header();

      // Display values entered by user
      printf("Program name is %s", argv[0]);
      printf("\nTime to sleep before terminating = %d ", mainSleep);
      printf("\nNumber of producer threads = %d ", producerThreadsToCreate);
      printf("\nNumber of consumer threads = %d ", consumerThreadsToCreate);
      printf("\n\n");

      // Initialize semaphores, muxtex, attributes, and counters
      initialize();

      // Create producer threads
      int i;
      int j;
      for(i = 0; i < producerThreadsToCreate; i++)
      {
          pthread_create(&pTID, &attr, producer, NULL);
      }

      // Create consumer threads
      for(j = 0; j < consumerThreadsToCreate; j++)
      {
          pthread_create(&cTID, &attr, consumer, NULL);
      }


      // Sleep for the amount of time that the user specified in seconds
      fflush(stdout);
      sleep(mainSleep);

      // Exit simulation
      printf("End Multithreaded Producer-Consumer Simulation.\n");
      return 0;
}

//==================    FUNCTIONS   ==================
/*
 * PURPOSE: Displays the header before running the producer-consumer
 *                  simulation.
 */
void print_header()
{
     printf ("\n===========================================================\n");
	printf ("Authors         : Pierre Pelletier and Jason Sneddon\n");
	printf ("Course          : CS433 - Operating Systems\n");
	printf ("Assignment 4    : Multi-threaded Producer-Consumer Solution\n");
	printf ("Date            : November 23, 2016\n");
	printf ("===========================================================\n\n");
}

/*
 * PURPOSE: Function to initialize the mutual exclusion
 *          object mutex, along with the empty and full
 *          semaphores.
 */
void initialize()
{
     // Create the mutex lock
     pthread_mutex_init(&mutex, NULL);

     // Create the full semaphore
     sem_init(&full, 0, 0);

     // Create the empty semaphore
     sem_init(&empty, 0, BUFFER_SIZE);

     // Initialize attributes and counters
     pthread_attr_init(&attr);
     srand(time(NULL));

     count = 0;
     itemCount = 0;
}

/*
 * PURPOSE: Returns a random number between 1 and 1000
 */
int randomNumber()
{
     int randNum;
     randNum = rand() % 1000 + 1;
     return randNum;
}


/*
 * PURPOSE: Displays the content of the shared buffer
 * @PARAMS:
 *          int c is the integer count, which represents the number of items in
 *          the buffer.
 */
void displayBuffer(int c)
{
     int x = 0;
     int tempCount = c;
     printf("The current content of the buffer is [ ");
     fflush(stdout);

     if(x == tempCount)
     {
          printf("empty");
          fflush(stdout);
     }

     for(x = 0; x < tempCount; x++)
     {
          if(tempCount != 0)
          {
               printf("%d", buffer[x]);
               fflush(stdout);

               if(x + 1 != tempCount)
               {
                    printf(", ");
                    fflush(stdout);
               }
          }
     }
     printf(" ]\n\n");
     fflush(stdout);
}

/*
 * PURPOSE: The Producer thread will alternate between sleeping for
 *                  a random period of time and inserting a random integer
 *                  into the buffer.
 */
void *producer(void *param)
{
     buffer_item item;

     while(TRUE)
     {
          // Sleep for a random period of time between 1 and main sleep time
          int randSleep = rand() % mainSleep + 1;
          sleep(randSleep);

          // Before entering critical section, wait for the empty signal then acquire the mutex lock
          sem_wait(&empty);
          pthread_mutex_lock(&mutex);

          // Produce a random number between 1 and 1000
          item = randomNumber();

          // Add item to the buffer if there is no error
          if(insert_item(item))
          {
               printf("Report error condition");
          }

          // Leaving critical section so release the mutex lock and signal full
          pthread_mutex_unlock(&mutex);
          sem_post(&full);
     }
}

/*
 * PURPOSE: The Consumer will also sleep for a random period of time
 *                  and, upon awakening, the consumer will attempt to
 *                  remove an item from the buffer.
 *
 */
void *consumer(void *param)
{
     buffer_item item;

     while(TRUE)
     {
          // Sleep for a random period of time between 1 and main sleep time
          int randomSleep = rand() % mainSleep + 1;
          sleep(randomSleep);

          // Wait for the producer to signal full then acquire mutex lock
          sem_wait(&full);
          pthread_mutex_lock(&mutex);

          // Remove item from buffer if no error
          if(remove_item(&item))
          {
               printf("Report error condition.");
          }

          // Done with critical section so release mutex lock and signal empty
          pthread_mutex_unlock(&mutex);
          sem_post(&empty);
     }
}


/*
 * PURPOSE: Buffer operation used by the Producer thread
 *          to insert an item into the buffer.
 * @PARAMS:
 *          buffer_item item is the random number produced by
 *          the producer that needs to be inserted into the buffer.
 *
 * RETURNS:
 *    - 0 if successful
 *    - Otherwise -1 indicating an error
 */
int insert_item(buffer_item item)
{
     if (count < BUFFER_SIZE)
     {
          // Insert item into buffer
          buffer[count] = item;
          count++;

          itemCount = count;

          // Print out the contents of the shared buffer
          printf("Item %d inserted by a producer. \n", itemCount);
          fflush(stdout);
          displayBuffer(count);

          return 0;
     }
     else
     {
          return -1;
     }
}

/*
 * PURPOSE: Buffer operation used by the Consumer thread to
 *          remove an item from the buffer.
 * @PARAMS:
 *          buffer_item *item is a pointer to the random number in the
 *          buffer that needs to be removed by the consumer.
 * RETURNS:
 *          Returns 0 if successful.
 *          Otherwise, returns -1.
 */
int remove_item(buffer_item *item)
{
     if(count > 0)
     {
          *item = buffer[(count - 1)];
          itemCount = count;
          count--;

          // Print out the contents of the shared buffer
          printf("Item %d removed by a consumer. \n", itemCount);
          fflush(stdout);
          displayBuffer(count);
          return 0;
     }
     else
     {
          // Error buffer empty
          return -1;
     }
     itemCount = itemCount - 1;
}

//================   END MAIN.C  ===================

