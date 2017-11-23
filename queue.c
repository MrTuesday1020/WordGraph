// Queue ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

typedef struct node {
   int data;
   struct node *next;
} NodeT;

typedef struct QueueRep {
   int   length;
   NodeT *head;
   NodeT *tail;
} QueueRep;

// set up empty queue
queue newQueue() {
   queue Q = malloc(sizeof(QueueRep));
   Q->length = 0;
   Q->head = NULL;
   Q->tail = NULL;
   return Q;
}

// remove unwanted queue
void dropQueue(queue Q) {
   NodeT *curr = Q->head;
   while (curr != NULL) {
      NodeT *temp = curr->next;
      free(curr);
      curr = temp;
   }
   free(Q);
}

// check whether queue is empty
int QueueIsEmpty(queue Q) {
   return (Q->length == 0);
}

// insert an int at end of queue
void QueueEnqueue(queue Q, int d) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   new->data = d;
   new->next = NULL;
   if (Q->tail != NULL) {
      Q->tail->next = new;
      Q->tail = new;
   } else {
      Q->head = new;
      Q->tail = new;
   }
   Q->length++;
}

// remove int from front of queue
int QueueDequeue(queue Q) {
   assert(Q->length > 0);
   NodeT *p = Q->head;
   Q->head = Q->head->next;
   if (Q->head == NULL) {
      Q->tail = NULL;
   }
   Q->length--;
   int d = p->data;
   free(p);
   return d;
}

// print the whole queue
void printQueue(queue Q){
   NodeT *p = Q->head;
   while (p) {
      int d = p->data;
      printf("%d ", d);
      p = p->next;
   }
   printf("\n");
}


// remove int from front of queue
int getDataByIndex(queue Q, int index) {
   NodeT *p = Q->head;
   int i;
   for(i=0; i<index; i++){
      p = p->next;
   }
   int d = p->data;
   return d;
}

// check if the data exists
bool DataExists(queue Q, int data){
   bool result = false;
   
   NodeT *p = Q->head;
   while (p != NULL && result== false) {
      int d = p->data;
      if(d == data){
         result = true;
      }
      p = p->next;
   }
   
   return result;
}