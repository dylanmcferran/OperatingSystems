#include "giorgio.h"

//function used to return a random value between min and max
int randomNum(int min, int max) {
	if(min > max) {
		printf("COULD NOT GENERATE RANDOM NUMBERS WITH THE ARGUENTS PROVIDED");
		exit(2);
	}
	return (rand() % (max+1 - min)) + min;
}

//function used to determine if a job terminates after exiting the CPU
int probQuit() {
	//generate a random number(1,100) and compare it to QUIT_PROB*100
	if (randomNum(1,100) <= QUIT_PROB*100) {
		return 1;
	}
	return 0;	
}