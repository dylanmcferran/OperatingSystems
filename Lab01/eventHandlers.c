#include "giorgio.h"

//keeps track of how long each server is busy
int cpuTimeBusy = 0;
int disk1TimeBusy = 0;
int disk2TimeBusy = 0;

//keeps track of the max response time for each server
int cpuMaxResponseTime = 0;
int disk1MaxResponseTime = 0;
int disk2MaxResponseTime = 0;

//keeps track of the cumulative response time for each server
int cpuCumResponseTime = 0;
int disk1CumResponseTime = 0;
int disk2CumResponseTime = 0;

//keeps track of the number of events that make it to each server
int numOfCPUEvents = 0;
int numOfDisk1Events = 0;
int numOfDisk2Events = 0;

//ints used to keep track if each server is busy
int isCPUBusy = 0;
int isDisk1Busy = 0;
int isDisk2Busy = 0;

//function to handle CPU_STARTED
void handleCPU_STARTED(Event event) {
	//equeue the event to the cpuQueue
	enqueue(&cpuQueue, event);
	//enter the block if the cpu is idle
	if(!isCPUBusy) {
		//set cpu to busy
		isCPUBusy = 1;
		//dequeue the current job
		Event currentJob = dequeue(&cpuQueue);
		//generate how long it will use the cpu
		int runTime = randomNum(CPU_MIN, CPU_MAX);
		//enqueue the event back into the event queue after changing the time and the eventType
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, CPU_FINISHED, currentJob.eventID));
		//log the event
		fprintf(logFile, "At %d job %d started using the cpu\n", currentTime, currentJob.eventID);
		//update cpuTimeBusy
		cpuTimeBusy += runTime;
		//calculate response time
		int responseTime = currentTime - currentJob.time;
		//if response time is greater than the previous max, set it as the new max
		if(responseTime > cpuMaxResponseTime) {
			cpuMaxResponseTime = responseTime;
		}
		//update cpuCumResponseTime
		cpuCumResponseTime += responseTime;
		//update numOfCPUEvents
		numOfCPUEvents++;
	}
}

//function to handle CPU_FINISHED
void handleCPU_FINISHED(Event event) {
	//set the cpu to idle
	isCPUBusy = 0;
	//log the event
	fprintf(logFile, "At %d job %d finished using the cpu\n", currentTime, event.eventID);
	//enter the statement if the job is finished after using the cpu
	//set the job up for a disk operation
	if(probQuit()) {
		handleJOB_TERMINATED(event);
	} else {
		if(isQ1Shorter(disk1Queue, disk2Queue)){
			priorityEnqueue(&eventQueue, createEventWithID(currentTime+event.time, DISK1_STARTED, event.eventID));
		} else {
			priorityEnqueue(&eventQueue, createEventWithID(currentTime+event.time, DISK2_STARTED, event.eventID));
		}
	}
}

//function to handle DISK1_STARTED
void handleDISK1_STARTED(Event event) {
	//enqueue the event to the disk1Queue
	enqueue(&disk1Queue, event);
	//enter the block if disk1 is idle
	if(!isDisk1Busy) {
		//set disk1 to busy
		isDisk1Busy = 1;
		//dequeue the current job
		Event currentJob = dequeue(&disk1Queue);
		//generate how long it will use disk1
		int runTime = randomNum(DISK1_MIN, DISK1_MAX);
		//enqueue the event back into the event queue after changing the time and the eventType
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, DISK1_FINISHED, currentJob.eventID));
		//log the event
		fprintf(logFile, "At %d job %d started using disk1\n", currentTime, currentJob.eventID);
		//update disk1TimeBusy
		disk1TimeBusy += runTime;
		//calculate response time
		int responseTime = currentTime - currentJob.time;
		//if response time is greater than the previous max, set it as the new max
		if(responseTime > disk1MaxResponseTime) {
			disk1MaxResponseTime = responseTime;
		}
		//update disk1CumResponseTime
		disk1CumResponseTime += responseTime;
		//update numOfDisk1Events
		numOfDisk1Events++;
	}
}

//function to handle DISK1_FINISHED
void handleDISK1_FINISHED(Event event) {
	//return the job to the cpu queue
	enqueue(&cpuQueue, createEventWithID(currentTime+event.time, CPU_STARTED, event.eventID));
	//set disk1 to idle
	isDisk1Busy = 0;
	//log the event
	fprintf(logFile, "At %d job %d finished using disk1\n", currentTime, event.eventID);
}

//function to handle DISK2_STARTED
void handleDISK2_STARTED(Event event) {
	//enqueue the event to the disk2Queue
	enqueue(&disk2Queue, event);
	//enter the block if disk2 is idle
	if(!isDisk2Busy) {
		//set disk2 to busy
		isDisk2Busy = 1;
		//dequeue the current job
		Event currentJob = dequeue(&disk2Queue);
		//generate how long it will use disk2
		int runTime = randomNum(DISK2_MIN, DISK2_MAX);
		//enqueue the event back into the event queue after changing the time and the eventType
		priorityEnqueue(&eventQueue, createEventWithID(currentTime+runTime, DISK2_FINISHED, currentJob.eventID));
		//log the event
		fprintf(logFile, "At %d job %d started using disk2\n", currentTime, currentJob.eventID);
		//update disk2TimeBusy
		disk2TimeBusy += runTime;
		//calculate response time
		int responseTime = currentTime - currentJob.time;
		//if response time is greater than the previous max, set it as the new max
		if(responseTime > disk2MaxResponseTime) {
			disk2MaxResponseTime = responseTime;
		}
		//update disk2CumResponseTime
		disk2CumResponseTime += responseTime;
		//update numOfDisk2Events
		numOfDisk2Events++;
	}
}

//function to handle DISK1_STARTED
void handleDISK2_FINISHED(Event event) {
	//return the job to the cpu queue
	enqueue(&cpuQueue, createEventWithID(currentTime+event.time, CPU_STARTED, event.eventID));
	//set disk2 to idle
	isDisk2Busy = 0;
	//log the event
	fprintf(logFile, "At %d job %d finished using disk1\n", currentTime, event.eventID);
}

//function to handle JOB_ARRIVED
void handleJOB_ARRIVED(Event event) {
	//log the event
	fprintf(logFile, "At %d job %d arrived\n", currentTime, event.eventID);
	//determine the arrival for the next job to enter the system and add it to the eventQueue
	priorityEnqueue(&eventQueue, createEvent(currentTime+randomNum(ARRIVE_MIN, ARRIVE_MAX), JOB_ARRIVED));
	//send the event to get handled by the cpu
	handleCPU_STARTED(event);
}

//function to handle JOB_TERMINATED
void handleJOB_TERMINATED(Event event) {
	//log the event
	fprintf(logFile, "At %d job %d terminated\n", currentTime, event.eventID);
}

//function to handle SIMULATION_TERMINATED
void handleSIMULATION_TERMINATED(Event event) {
	//set isSimulationFinished to true
	isSimulationFinished = 1;
	//log the event
	fprintf(logFile, "At %d the simulation terminated\n\n", currentTime);
}