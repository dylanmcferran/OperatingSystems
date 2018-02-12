# Variable for compiler
CC=gcc
# Variable for compiler options
CFLAGS=-c -Wall -I.
# Variable for cleanup command
# to clean .o file
CLEANUP=rm -rf *o test.exe

# Entry point and exit point for call to "make".
# Compile executable.
all:
	gcc -o test.exe main.c readConf.c event.c queue.c random.c logFile.c -lm

# Remove object
clean:
	$(CLEANUP)
