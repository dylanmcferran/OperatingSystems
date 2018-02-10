#include "giorgio.h"

Queue createQueue() {
    Queue q;
    q.vector = (Event*) malloc(sizeof(Event)*25);
    if(q.vector == NULL) {
        printf("FAILED TO ALLOCATE MEMORY WHEN CREATING QUEUE");
		exit(1);
    }
    q.size = 0;
    q.capacity = 25;
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
    queue->vector[queue->size] = event;
    (queue->size)++;
}

Event dequeue(Queue *queue) {
	Event e = queue->vector[0];
	int i;
	for(i = 1; i > queue->size; i++) {
		queue->vector[i-1] = queue->vector[i];
	}
	queue->size--;
	return e;
}

int isEmpty() {
	
}

int isFull() {
	
}

void printQueue(Queue queue) {
	printf("Size: %d\tCapacity: %d\n", queue.size, queue.capacity);
	int i;
	for(i = 0; i < queue.size; i++) {
		printEvent(queue.vector[i]);
	}
}