#include "giorgio.h"

int isCPUBusy = 0;
int isDisk1Busy = 0;
int isDisk2Busy = 0;

void handleCPU_STARTED(Event event) {
	enqueue(&cpuQueue, event);
	if(!isCPUBusy) {
		isCPUBusy = 1;
		
		Event currentJob = dequeue(&cpuQueue);
		int runTime = randomNum(CPU_MIN, CPU_MAX);
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, CPU_FINISHED, currentJob.eventID));
		fprintf(logFile, "At %d job %d started using the cpu\n", currentTime, currentJob.eventID);
	}
}
void handleCPU_FINISHED(Event event) {
	isCPUBusy = 0;
	fprintf(logFile, "At %d job %d finished using the cpu\n", currentTime, event.eventID);
	if(probQuit()) {
		handleJOB_TERMINATED(event);
		//priorityEnqueue();
	} else {
		if(getShortestQueue(disk1Queue, disk2Queue)){
			priorityEnqueue(&eventQueue, createEventWithID(currentTime+event.time, DISK1_STARTED, event.eventID));
		} else {
			priorityEnqueue(&eventQueue, createEventWithID(currentTime+event.time, DISK2_STARTED, event.eventID));
		}
	}
}
void handleDISK1_STARTED(Event event) {
	enqueue(&disk1Queue, event);
	if(!isDisk1Busy) {
		isDisk1Busy = 1;
		
		Event currentJob = dequeue(&disk1Queue);
		int runTime = randomNum(DISK1_MIN, DISK1_MAX);
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, DISK1_FINISHED, currentJob.eventID));
		fprintf(logFile, "At %d job %d started using disk1\n", currentTime, currentJob.eventID);
	}
}
void handleDISK1_FINISHED(Event event) {
	//return job to cpu
	enqueue(&cpuQueue, createEventWithID(currentTime+event.time, CPU_STARTED, event.eventID));
	//
	isDisk1Busy = 0;
	fprintf(logFile, "At %d job %d finished using disk1\n", currentTime, event.eventID);
}
void handleDISK2_STARTED(Event event) {
	enqueue(&disk2Queue, event);
	if(!isDisk2Busy) {
		isDisk2Busy = 1;
		
		Event currentJob = dequeue(&disk2Queue);
		int runTime = randomNum(DISK2_MIN, DISK2_MAX);
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, DISK2_FINISHED, currentJob.eventID));
		fprintf(logFile, "At %d job %d started using disk2\n", currentTime, currentJob.eventID);
	}
}
void handleDISK2_FINISHED(Event event) {
	//return job to cpu
	enqueue(&cpuQueue, createEventWithID(currentTime+event.time, CPU_STARTED, event.eventID));
	//
	isDisk2Busy = 0;
	fprintf(logFile, "At %d job %d finished using disk1\n", currentTime, event.eventID);
}
void handleJOB_ARRIVED(Event event) {
	//set surrent time
	//currentTime = event.time;
	//print statement
	fprintf(logFile, "At %d job %d arrived\n", currentTime, event.eventID);
	//determine the arrival for the next job to enter the system and add it to the eventQueue
	priorityEnqueue(&eventQueue, createEvent(currentTime+randomNum(ARRIVE_MIN, ARRIVE_MAX), JOB_ARRIVED));
	//add the event to the cpuQueue
	//enqueue(&cpuQueue, event);
	//send the event to the cpu
	handleCPU_STARTED(event);
}
void handleJOB_TERMINATED(Event event) {
	//print statement
	fprintf(logFile, "At %d job %d terminated\n", currentTime, event.eventID);
}

void handleSIMULATION_TERMINATED(Event event) {
	isSimulationFinished = 1;
	//print statement
	fprintf(logFile, "At %d the simulation terminated\n", currentTime);
}