#include "giorgio.h"

Queue eventQueue;
Queue cpuQueue;
Queue disk1Queue;
Queue disk2Queue;

int currentTime;
int isSimulationFinished;

int main(void) {
    
	/*Queue q1 = createQueue();
	enqueue(&q1, createEvent(0, CPU_STARTED));
	enqueue(&q1, createEvent(1, CPU_FINISHED));
	enqueue(&q1, createEvent(2, DISK1_STARTED));
	enqueue(&q1, createEvent(3, DISK2_STARTED));
	printQueue(q1);
	dequeue(&q1);
	dequeue(&q1);
	dequeue(&q1);
	printQueue(q1);
	printf("\n");
	Queue q2 = createQueue();
	priorityEnqueue(&q2, createEvent(2, CPU_STARTED));
	priorityEnqueue(&q2, createEvent(1, CPU_FINISHED));
	priorityEnqueue(&q2, createEvent(5, DISK1_STARTED));
	priorityEnqueue(&q2, createEvent(3, DISK2_STARTED));
	printQueue(q2);
	dequeue(&q2);
	dequeue(&q2);
	dequeue(&q2);
	printQueue(q2);*/
	
	openLogFile();
	
	readConfigFile("conf.txt");
	srand(SEED);
	
	writeConstantsToLogFile();
	
	currentTime = INIT_TIME;
	isSimulationFinished = 0;
	int numLoops;
	
	eventQueue = createQueue();
	cpuQueue = createQueue();
	disk1Queue = createQueue();
	disk2Queue = createQueue();
	
	priorityEnqueue(&eventQueue, createEvent(INIT_TIME, JOB_ARRIVED));
	priorityEnqueue(&eventQueue, createEventWithID(FIN_TIME, SIMULATION_TERMINATED, INT_MAX));
	
	while(!isEmpty(&eventQueue) && !isSimulationFinished) {
		
		Event event = dequeue(&eventQueue);
		currentTime = event.time;
		
		if(event.eventType == CPU_STARTED) {
			handleCPU_STARTED(event);
		} else if (event.eventType == CPU_FINISHED) {
			handleCPU_FINISHED(event);
		} else if (event.eventType == DISK1_STARTED) {
			handleDISK1_STARTED(event);
		} else if (event.eventType == DISK1_FINISHED) {
			handleDISK1_FINISHED(event);
		} else if (event.eventType == DISK2_STARTED) {
			handleDISK2_STARTED(event);
		} else if (event.eventType == DISK2_FINISHED) {
			handleDISK2_FINISHED(event);
		} else if (event.eventType == JOB_ARRIVED) {
			handleJOB_ARRIVED(event);
		} else if (event.eventType == JOB_TERMINATED) {
			handleJOB_TERMINATED(event);
		} else if (event.eventType == SIMULATION_TERMINATED) {
			handleSIMULATION_TERMINATED(event);
		}
		numLoops++;
		updateQueueTotals();
	}
	
	logStats(numLoops);
	
	//free the allocated memory
	deleteQueue(&eventQueue);
	deleteQueue(&cpuQueue);
	deleteQueue(&disk1Queue);
	deleteQueue(&disk2Queue);
	//close the logFile
	closeLogFile();
	
    return 0;
}
