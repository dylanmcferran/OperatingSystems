#include "giorgio.h"

int SEED;
int INIT_TIME;
int FIN_TIME;
int ARRIVE_MIN;
int ARRIVE_MAX;
double QUIT_PROB;
int CPU_MIN;
int CPU_MAX;
int DISK1_MIN;
int DISK1_MAX;
int DISK2_MIN;
int DISK2_MAX;

// function to read a configuration file and save the contents to the appropriate variables
void readConfigFile(char *fileName) {
    // Open file to read
    FILE *file;
    file = fopen(fileName, "r");
    // Check that the file is open
    if(file == NULL){
        printf("file could not be opened");
        exit(1);
    }
    //read each line and save the values to each variable
    SEED = time(NULL);
    fscanf(file, "INIT_TIME %d\n", &INIT_TIME);
    fscanf(file, "FIN_TIME %d\n", &FIN_TIME);
    fscanf(file, "ARRIVE_MIN %d\n", &ARRIVE_MIN);
    fscanf(file, "ARRIVE_MAX %d\n", &ARRIVE_MAX);
    fscanf(file, "QUIT_PROB %lf\n", &QUIT_PROB);
    fscanf(file, "CPU_MIN %d\n", &CPU_MIN);
    fscanf(file, "CPU_MAX %d\n", &CPU_MAX);
    fscanf(file, "DISK1_MIN %d\n", &DISK1_MIN);
    fscanf(file, "DISK1_MAX %d\n", &DISK1_MAX);
    fscanf(file, "DISK2_MIN %d\n", &DISK2_MIN);
    fscanf(file, "DISK2_MAX %d\n", &DISK2_MAX);

    //printf("%d\n%d\n%d\n%d\n%d\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n", SEED,INIT_TIME,FIN_TIME,ARRIVE_MIN,ARRIVE_MAX,QUIT_PROB,CPU_MIN,CPU_MAX,DISK1_MIN,DISK1_MAX,DISK2_MIN,DISK2_MAX);

    // Close file
    fclose(file);
}
