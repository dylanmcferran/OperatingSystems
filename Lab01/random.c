#include "giorgio.h"

int randomNum(int min, int max) {
	if(min > max) {
		printf("COULD NOT GENERATE RANDOM NUMBERS WITH THE ARGUENTS PROVIDED");
		exit(2);
	}
	return (rand() % (max+1 - min)) + min;
}

int probQuit() {
	if (randomNum(1,100) <= QUIT_PROB*100) {
		return 1;
	}
	return 0;	
}