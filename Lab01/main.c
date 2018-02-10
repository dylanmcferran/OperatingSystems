#include "giorgio.h"

int main(void) {
    /*readConfigFile("conf.txt");
	srand(SEED);
	printf("rand num: %d\n", randomNum(5,100));
	printf("rand num: %d\n", probQuit());*/
	
	//Event e1 = createEvent(0, 1);
	//Event e2 = createEvent(20, 2);
	//Event e3 = createEvent(30, 3);
	
	Queue q1 = createQueue();
	enqueue(&q1, createEvent(0, 1));
	enqueue(&q1, createEvent(10, 2));
	enqueue(&q1, createEvent(19, 3));
	
	printQueue(q1);
	/*
	Queue q = createQueue();
	enqueue(&q, createEvent(37,0));
	printQueue(q);
	enqueue(&q, createEvent(12,1));
	printQueue(q);
	enqueue(&q, createEvent(20,2));
	printQueue(q);
	Event e = dequeue(&q);
	printQueue(q);
	printEvent(e);*/
	
    return 0;
}
