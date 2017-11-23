// Queue ADT header file
#include <stdbool.h>

typedef struct QueueRep *queue;

queue newQueue();               	// set up empty queue
void  dropQueue(queue);         	// remove unwanted queue
int   QueueIsEmpty(queue);      	// check whether queue is empty
void  QueueEnqueue(queue, int); 	// insert an int at end of queue
int   QueueDequeue(queue);      	// remove int from front of queue

void  printQueue(queue);			// print the whole queue
int   getDataByIndex(queue, int);	// get the word by index of queue
bool  DataExists(queue, int);		// check if the data exists