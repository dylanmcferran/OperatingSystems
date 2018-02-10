#ifndef giorgio
	#define giorgio
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	
	#define CPU_STARTED 1
    #define CPU_FINISHED 2
	#define DISK1_STARTED 3
	#define DISK1_FINISHED 4
	#define DISK2_STARTED 5
	#define DISK2_FINISHED 6
	#define JOB_ARRIVED 7
	#define JOB_TERMINATED 8

	
	typedef struct {
		int time;
        int eventID;
		int eventType;
    }Event;
	
	typedef struct {
        Event *vector;
		int size;
        int capacity;
    }Queue;
	
	//readConf
	void readConfigFile(char *filename);
	
	//random
	int randomNum(int min, int max);
	int probQuit();
	
	//queue
	Queue createQueue();
	void enqueue(Queue *queue, Event event);
	void priorityEnqueue(Queue *queue, Event event);
	Event dequeue(Queue *queue);
	void printQueue(Queue queue);
	
	extern int SEED;
	extern int INIT_TIME;
	extern int FIN_TIME;
	extern int ARRIVE_MIN;
	extern int ARRIVE_MAX;
	extern double QUIT_PROB;
	extern int CPU_MIN;
	extern int CPU_MAX;
	extern int DISK1_MIN;
	extern int DISK1_MAX;
	extern int DISK2_MIN;
	extern int DISK2_MAX;

#endif
