######################################################
# This is the makefile for Programming Assignment 4
# Producer-Consumer Problem
#
# Group name - pierre006_n_snedd001
# CS433 - OS COURSE
# November 23, 2016
#
#######################################################
CC = gcc

# -g for debugging. Change to -O or -O2 for optimized code.
CFLAGS = -O2
LIB = -lm -pthread
LDFLAGS = -L.

# target executable (output)
PROG = myThread

# .c files.
SRC = main.c

# object files for the target.
OBJ = $(SRC:.c=.o)

all : $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
