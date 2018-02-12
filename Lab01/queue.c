#include "giorgio.h"

int initialCap = 25;

Queue createQueue() {
    Queue q;
    q.vector = (Event*) malloc(sizeof(Event)*initialCap);
    if(q.vector == NULL) {
        printf("FAILED TO ALLOCATE MEMORY WHEN CREATING QUEUE");
		exit(1);
    }
    q.size = 0;
    q.capacity = initialCap;
    return q;
}

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
    } else {
        printf("QUEUE COULD NOT BE DELETED. IT IS ALREADY EMPTY.");
        exit(1);
    }
}

void enqueue(Queue *queue, Event event) {
     if(queue->size == queue->capacity) {
        queue->vector = (Event*) realloc(queue->vector, sizeof(Event)*queue->capacity*2);

        if(queue->vector == NULL){
            printf("FAILED TO REALLOCATE MEMORY\n");
            exit(1);
        }
        queue->capacity *= 2;
    }
    queue->vector[queue->size] = event;
    (queue->size)++;
}

void priorityEnqueue(Queue *queue, Event event) {
     if(queue->size == queue->capacity) {
        queue->vector = (Event*) realloc(queue->vector, sizeof(Event)*queue->capacity*2);

        if(queue->vector == NULL){
            printf("FAILED TO REALLOCATE MEMORY\n");
            exit(1);
        }
        queue->capacity *= 2;
    }
    
	int i;
	int j;
	for(i = 0; i < queue->size; i++) {
		if(event.time < queue->vector[i].time) {
			for(j = queue->size; j >= i; j--) {
				queue->vector[j] = queue->vector[j-1];
			}
			queue->vector[i] = event;
			break;
		}
	}
	if(i == queue->size) {
		queue->vector[queue->size] = event;
	}
	(queue->size)++;
}

Event dequeue(Queue *queue) {
	if(isEmpty(queue)) {
		printf("FAILED TO DEQUEUE EVENT, QUEUE IS EMPTY");
		exit(1);
	}
	
	Event e = queue->vector[0];
	int i;
	for(i = 1; i < queue->size; i++) {
		queue->vector[i-1] = queue->vector[i];
	}
	queue->size--;
	return e;
}

int isEmpty(Queue *queue) {
	if(queue->size == 0) {
		return 1;
	}
	return 0;
}

void printQueue(Queue queue) {
	printf("Size: %d\tCapacity: %d\n", queue.size, queue.capacity);
	int i;
	for(i = 0; i < queue.size; i++) {
		printEvent(queue.vector[i]);
	}
}

int getShortestQueue(Queue q1, Queue q2) {
	if(q1.size < q2.size) {
		return 1;
	} else if(q2.size < q1.size) {
		return 0;
	}
	return randomNum(0,1);
}