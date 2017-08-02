#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define MAX_NUMBER_OF_PARAMS 8
#define MAX_HISTORY_SIZE 100

/*Function prototypes */

//Function to get the size of the history buffer
int sizeOfBuffer();

//Function that adds a command to the history buffer if the size of the buffer is not exceeded.
//Otherwise, clear the first command in the buffer, and add the command there.
//Parameter - cmdToAdd is the command to be added.
void addToHistory(char *cmdToAdd);

//Function to display the history buffer
void displayHistory();

//Function to set recent command
void setRecentCommand(int *recCom);

//Function to get most recent command
int getRecentCommand();

//Function to clear the history buffer
int clearHistory(char *historyBuffer[]);

//Function to parse a string of 1 or more commands entered by the user
void parsecmd(char *cmd, char **params);

int elemIndex;
int historyCount;
char *historyBuffer[MAX_HISTORY_SIZE];


//This is a simple shell program that includes the UNIX std library.
//its primary purpose is to take in commands from a user and execute them.
//it will read in processes, fork them, and execute them.
//the parent process will wait for the child process to execute unless
//an ampersand is entered after a command in which case the parent and child
//processes wil run concurrently
int main(void)
{
     printf ("====================================================\n");
	printf ("Authors      : Pierre Pelletier and Jason Sneddon\n");
	printf ("Course       : CS433 - Operating Systems\n");
	printf ("Assignment2  : Simple Shell Program\n");
	printf ("Date         : 10/10/2016\n");
	printf ("====================================================\n");

     char *args[MAX_LINE / 2 + 1];
     int should_run = 1;
     printf("\n");
     clearHistory(historyBuffer);


     while (should_run != 0)
     {
          printf("\nosh> ");
          fflush(stdout);

          //c-string to store command entered by user
          char command[20];
          //c-string used to store exit command for comparison later
          char exitCMD[5] = "exit";
          //c-string used to store "&" command for comparison later
          char amp[2] = "&";
          //status of the child process
          int status;

          scanf("%s", command);

          parsecmd(command, args);

          //Add command to history buffer
          addToHistory(*args);

          //check to see if command is the 'exit' command
          if (strcmp(command, exitCMD) == 0)
          {
               printf("Program Terminated\n");
               should_run = 0;
               exit(0);
          }

          //Check if command is history
          char hist[8] = "history";
          if ( strcmp(command, hist) == 0)
          {
               displayHistory();
        	     continue;
          }

          //fork a child process
          pid_t pid;
          pid = fork();

          //Error
    		if(pid < 0)
    		{
               fprintf(stderr, "Fork Failed.");
               return 1;
    		}
    		//Child process will execute user command
          else if(pid == 0)
          {
               //Check if command is !!
        	     char execRecent[3] = "!!";
               if(strcmp(command, execRecent) == 0)
        	     {
                    //get the most recent command in the history buffer
				int rec = getRecentCommand();

				if(rec < 0)
				{
                         printf("No commands in history.\n");
					continue;
				}

				//Execute command
				rec = rec - 1;
				printf("Recent command is: %s", historyBuffer[rec - 1]);
				printf("\n");
				execvp(historyBuffer[rec - 1], args);
				continue;
        	      }
        	      //Check to see if command is !N
        	      if(command[0] == '!')
        	      {
                     int commandNum;
                     int one = 1;

                     if(isdigit(command[1]))
                     {
                          //Get the command number to execute and convert to int
                          commandNum = atoi(&command[one]);

                          //User command exceeds historyBuffer size
                          if(commandNum > historyCount)
                          {
                               printf("No such command in history.\n");
                          }
                          else
                          {
                               //Execute Nth command
                               printf("Command %i is: %s", commandNum, historyBuffer[commandNum-1]);
                               printf("\n");
                               execvp(historyBuffer[commandNum - 1], args);
                          }
                     }
                     continue;
                }
                //Execute regular command
                else
        	      {
                     //Execute command
                     execvp(args[0], args);

                     //Incorrect command was entered
                     int executeReturn = execvp(args[0], args);

                     if(executeReturn == -1)
                     {
                          exit(0);
                     }
                }
        }
        //Parent process
        else
        {
             if (!(command == amp))
             {
                  wait(&status);
             }
		   else
		   {
                  exit(0);
		   }
        }
    }

    return 0;
} //end main


//Function to get the size of the history buffer
int sizeOfBuffer()
{
	return sizeof(historyBuffer) / sizeof(char*);
}

//Function that adds a command to the history buffer if the size of the buffer is not exceeded.
//Otherwise, clear the first command in the buffer, and add the command there.
//Parameter - cmdToAdd is the command to be added.
void addToHistory(char *cmdToAdd)
{
	if(historyCount < MAX_HISTORY_SIZE)
	{
		historyBuffer[historyCount] = strdup( cmdToAdd );
		historyCount++;
	}
	else
	{
		free( historyBuffer[0] );
		int i;
		for(i = 1; i < MAX_HISTORY_SIZE; i++)
		{
			historyBuffer[i - 1] = strdup( cmdToAdd );
		}
		historyCount++;
	}
	elemIndex = historyCount;
}

//Function to display the history buffer
void displayHistory()
{
	int elemIndex = historyCount-1;
	if(elemIndex == 0)
	{
		printf("No commands in history");
     }

	int count = 0;
	printf("\n");

	while(count < 10 && elemIndex >= 0)
	{
		printf("%i - ", elemIndex+1);
		printf("%s", historyBuffer[elemIndex]);
		printf("\n");
		elemIndex--;
		count++;
	}
}

//Function to set recent command
void setRecentCommand(int *recCom)
{
	*recCom = elemIndex;
}

//Function to get most recent command
int getRecentCommand()
{
	return elemIndex;
}

//Function to clear the history buffer
int clearHistory(char *historyBuffer[])
{
	int i;

	for(i = 0; i < sizeOfBuffer(); i++)
	{
		free(historyBuffer[i]);
		historyBuffer[i] = NULL;
	}
	return 0;
}
//Function to parse a string of 1 or more commands entered by the user
void parsecmd(char *cmd, char **params)
{
    int i;
    for (i = 0; i < MAX_NUMBER_OF_PARAMS; i++)
    {
        params[i] = strsep(&cmd, " ");

        if (params[i] == NULL)
        {
            break;
        }
    }
}
