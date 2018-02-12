#include "giorgio.h"

FILE *logFile;

void openLogFile() {
	
	logFile = fopen("log.txt", "w");
	
	if(logFile == NULL){
		printf("FAILED TO CREATE LOG FILE");
		exit(1);
	}
}

void closeLogFile() {
	fclose(logFile);
}

void writeConstantsToLogFile() {
	fprintf(logFile, "SEED %d\n", SEED);
	fprintf(logFile, "INIT_TIME %d\n", INIT_TIME);
    fprintf(logFile, "FIN_TIME %d\n", FIN_TIME);
    fprintf(logFile, "ARRIVE_MIN %d\n", ARRIVE_MIN);
    fprintf(logFile, "ARRIVE_MAX %d\n", ARRIVE_MAX);
    fprintf(logFile, "QUIT_PROB %lf\n", QUIT_PROB);
    fprintf(logFile, "CPU_MIN %d\n", CPU_MIN);
    fprintf(logFile, "CPU_MAX %d\n", CPU_MAX);
    fprintf(logFile, "DISK1_MIN %d\n", DISK1_MIN);
    fprintf(logFile, "DISK1_MAX %d\n", DISK1_MAX);
    fprintf(logFile, "DISK2_MIN %d\n", DISK2_MIN);
    fprintf(logFile, "DISK2_MAX %d\n\n", DISK2_MAX);
}