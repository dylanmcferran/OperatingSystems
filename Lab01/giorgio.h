#ifndef giorgio
	#define giorgio
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <limits.h>
	
	#define CPU_STARTED 1
    #define CPU_FINISHED 2
	#define DISK1_STARTED 3
	#define DISK1_FINISHED 4
	#define DISK2_STARTED 5
	#define DISK2_FINISHED 6
	#define JOB_ARRIVED 7
	#define JOB_TERMINATED 8
	#define SIMULATION_TERMINATED 9

	//structs
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
	
	//main
	extern int currentTime;
	extern int isSimulationFinished;
	
	//readConf
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
	void readConfigFile(char *filename);
	
	//random
	int randomNum(int min, int max);
	int probQuit();
	
	//event
	Event createEvent(int time, int eventType);
	Event createEventWithID(int time, int eventType, int eventID);
	char* getEventType(int eventType);
	void printEvent(Event e);
	
	//queue
	Queue createQueue();
	void enqueue(Queue *queue, Event event);
	void priorityEnqueue(Queue *queue, Event event);
	Event dequeue(Queue *queue);
	int isEmpty(Queue *queue);
	void printQueue(Queue queue);
	int getShortestQueue(Queue q1, Queue q2);
	
	//evntHandlers
	extern Queue eventQueue;
	extern Queue cpuQueue;
	extern Queue disk1Queue;
	extern Queue disk2Queue;
	void handleCPU_STARTED(Event event);
	void handleCPU_FINISHED(Event event);
	void handleDISK1_STARTED(Event event);
	void handleDISK1_FINSIHED(Event event);
	void handleDISK2_STARTED(Event event);
	void handleDISK2_FINISHED(Event event);
	void handleJOB_ARRIVED(Event event);
	void handleJOB_TERMINATED(Event event);
	
	//logFile
	extern FILE *logFile;
	void openLogFile();
	void closeLogFile();
	void writeConstantsToLogFile();
	
	//stats
	extern int maxEventQueue;
	extern double avgEventQueue;
	extern int maxCPUQueue;
	extern double avgCPUQueue;
	extern int maxDisk1Queue;
	extern double avgDisk1Queue;
	extern int maxDisk2Queue;
	extern double avgDisk2Queue;

#endif
