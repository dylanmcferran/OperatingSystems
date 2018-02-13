#include "giorgio.h"

int eventQueueTotal = 0;
int cpuQueueTotal = 0;
int disk1QueueTotal = 0;
int disk2QueueTotal = 0;

void updateQueueTotals() {
	eventQueueTotal += eventQueue.size;
	cpuQueueTotal += cpuQueue.size;
	disk1QueueTotal += disk1Queue.size;
	disk2QueueTotal += disk2Queue.size;
}


void logStats(int numLoops) {
	fprintf(logFile, "Average eventQueue size %f\n", (double)eventQueueTotal/numLoops);
	fprintf(logFile, "Average cpuQueue size %f\n", (double)cpuQueueTotal/numLoops);
	fprintf(logFile, "Average disk1Queue size %f\n", (double)disk1QueueTotal/numLoops);
	fprintf(logFile, "Average disk2Queue size %f\n\n", (double)disk2QueueTotal/numLoops);
	
	fprintf(logFile, "Max eventQueue size %d\n", eventQueue.max);
	fprintf(logFile, "Max cpuQueue size %d\n", cpuQueue.max);
	fprintf(logFile, "Max disk1Queue size %d\n", disk1Queue.max);
	fprintf(logFile, "Max disk2Queue size %d\n\n", disk2Queue.max);
	
	fprintf(logFile, "Utilization of cpu %f\n", (double)cpuTimeBusy/(FIN_TIME-INIT_TIME));
	fprintf(logFile, "Utilization of disk1 %f\n", (double)disk1TimeBusy/(FIN_TIME-INIT_TIME));
	fprintf(logFile, "Utilization of disk2 %f\n\n", (double)disk2TimeBusy/(FIN_TIME-INIT_TIME));
	
	fprintf(logFile, "Average response time for cpu %f\n", (double)cpuCumResponseTime/cpuTimeBusy);
	fprintf(logFile, "Average response time for disk1 %f\n", (double)disk1CumResponseTime/disk1TimeBusy);
	fprintf(logFile, "Average response time for disk2 %f\n\n", (double)disk2CumResponseTime/disk2TimeBusy);
	
	fprintf(logFile, "Maximum response time for cpu %d\n", cpuMaxResponseTime);
	fprintf(logFile, "Maximum response time for disk1 %d\n", disk1MaxResponseTime);
	fprintf(logFile, "Maximum response time for disk2 %d\n\n", disk2MaxResponseTime);
	
	fprintf(logFile, "Throughput for cpu %f\n", (double)numOfCPUEvents/cpuTimeBusy);
	fprintf(logFile, "Throughput for disk1 %f\n", (double)numOfDisk1Events/disk1TimeBusy);
	fprintf(logFile, "Throughput for disk2 %f\n\n", (double)numOfDisk2Events/disk2TimeBusy);
}