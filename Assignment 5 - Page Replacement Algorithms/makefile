##################################################
# Pierre Pelletier and Jason Sneddon
# CS433 - Operating Systems
# Assignment 5  - Page Replacement Simulation
# Date - December 9, 2016
##################################################

# use g++ for compiling c++ code
CC = g++

# compilation flags: -g for debugging. -02 for optimized code
CFLAGS = -O2 -Wall
# linked libraries
LIB = -lm
# link flags
LDFLAGS = -L.
# target executable (output)
PROG = pageReplace
# .c or .cpp source files
SRC = main.cpp
# object files for the target. Add more to this and next lines if there are more than one source files.
OBJ = $(SRC:.cpp=.o)

all : $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
