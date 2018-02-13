#include "giorgio.h"

//sets the initial capacity of a new queue
int initialCap = 25;

//function used to create a new queue
Queue createQueue() {
    Queue q;
    //allocates the memory needed to store the vector of events
	q.vector = (Event*) malloc(sizeof(Event)*initialCap);
    //checks to see if the memory successfully allocated
	if(q.vector == NULL) {
        printf("FAILED TO ALLOCATE MEMORY WHEN CREATING QUEUE");
		exit(1);
    }
    q.size = 0;
    q.capacity = initialCap;
	q.max = 0;
    return q;
}

//function used to delete a queue and free the memory tied to it
void deleteQueue(Queue *queue){
    if(queue->vector != NULL){
        free(queue->vector);
        queue->vector = NULL;
        if(queue->vector != NULL) {
            printf("FREE FAILED.");
            exit(1);
        }
        queue->size = 0;
        queue->capacity = 0;
		queue->max = 0;
    } else {
        printf("QUEUE COULD NOT BE DELETED");
        exit(1);
    }
}

//function used to add an event to a FIFO queue
void enqueue(Queue *queue, Event event) {
    //checks to see if the queue is at capacity and more memory needs to be allocated
	if(queue->size == queue->capacity) {
       //reallocates the memory so it can hold double the capacity of events
	   queue->vector = (Event*) realloc(queue->vector, sizeof(Event)*queue->capacity*2);
		//checks to see if the memory was successfully reallocated
        if(queue->vector == NULL){
            printf("FAILED TO REALLOCATE MEMORY\n");
            exit(1);
        }
		//sets the queue capacity to capacity*2
        queue->capacity *= 2;
    }
	//adds the event to the end of the queue
    queue->vector[queue->size] = event;
	//increments the size of the queue
    (queue->size)++;
	//used to keep track of the maximum number of events a queue has
	if(queue->max < queue->size) {
		(queue->max)++;
	}
}

//function used to mimic a sorted list. Events are sorted as they are added so the queue remains sorted at all times
void priorityEnqueue(Queue *queue, Event event) {
    //reallocates memory and doubles capacity
	if(queue->size == queue->capacity) {
        queue->vector = (Event*) realloc(queue->vector, sizeof(Event)*queue->capacity*2);
		//makes sure memory was successfully reallocated
        if(queue->vector == NULL){
            printf("FAILED TO REALLOCATE MEMORY\n");
            exit(1);
        }
		//doubles capacity
        queue->capacity *= 2;
    }
    
	int i;
	int j;
	//for loop that iterates through the queue to find what index the new element belongs in
	for(i = 0; i < queue->size; i++) {
		//enters the block if the new event's time is less than the event's time at the index
		if(event.time < queue->vector[i].time) {
			//for loop that moves every element from queue->size to i to the left one, making room for the new element 
			for(j = queue->size; j >= i; j--) {
				queue->vector[j] = queue->vector[j-1];
			}
			//insert the element
			queue->vector[i] = event;
			break;
		}
	}
	//if the element is greater than all the other elements, add it to the end of the queue
	if(i == queue->size) {
		queue->vector[queue->size] = event;
	}
	//increment size
	(queue->size)++;
	//used to keep track of the maximum number of events a queue has
	if(queue->max < queue->size) {
		(queue->max)++;
	}
}

//function used to dequeue the first element of a queue
Event dequeue(Queue *queue) {
	//if the queue is empty, exit
	if(isEmpty(queue)) {
		printf("FAILED TO DEQUEUE EVENT, QUEUE IS EMPTY");
		exit(1);
	}
	//save the event to be dequeued
	Event e = queue->vector[0];
	int i;
	//for loop that moves every element forward one spot, replacing the one that was removed
	for(i = 1; i < queue->size; i++) {
		queue->vector[i-1] = queue->vector[i];
	}
	//decrement the size
	queue->size--;
	//return the event
	return e;
}

//function used to test if a queue is empty
int isEmpty(Queue *queue) {
	if(queue->size == 0) {
		return 1;
	}
	return 0;
}

//function used to print a queue, used for debugging
void printQueue(Queue queue) {
	printf("Size: %d\tCapacity: %d\n", queue.size, queue.capacity);
	int i;
	for(i = 0; i < queue.size; i++) {
		printEvent(queue.vector[i]);
	}
}

//function that returns true if the first queue is shorter, false if the second queue is shorter, and a random value(0,1) if they are the same length
int isQ1Shorter(Queue q1, Queue q2) {
	if(q1.size < q2.size) {
		return 1;
	} else if(q2.size < q1.size) {
		return 0;
	}
	return randomNum(0,1);
}