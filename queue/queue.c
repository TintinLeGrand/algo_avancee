#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../list/list.h"

/**
 * @brief Creates a new, empty queue.
 *
 * @return A pointer to the newly created queue.
 */
 Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}


/**
 * @brief Checks whether the queue is empty.
 *
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue q) {
    return (q.front == NULL);
}


/**
 * @brief Prints all the elements in the queue, from front to rear.
 *
 * @param q The queue to print.
 */
void queuePrint(Queue q) {
    printList(q.front,0);
}


/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q A pointer to the queue to add the element to.
 * @param data The data to be added to the queue.
 */
void enqueue(Queue* q, int data) {
    if (q==NULL) {
        printf("Error enqueue: queue pointer is NULL\n");
        exit(1);
    }
    if(q->front==NULL){
        q->front = addKeyValueInList(NULL,NULL,data);
        q->rear = q->front;
    }
    else{
        q->rear->nextCell = addKeyValueInList(NULL,NULL,data);
        q->rear = q->rear->nextCell;
    }
}

/**
 * @brief Removes and returns the front element of the queue.
 *
 * @param q A pointer to the queue to remove the front element from.
 * @return The value stored in the front element of the queue.
 */
int dequeue(Queue* q) {
    if (q==NULL) {
        printf("Error dequeue: queue is NULL\n");
        exit(1);
    }
    if (isQueueEmpty(*q)) {
        printf("Error: queue is empty\n");
        exit(1);
    }

    int value = q->front->value;
    q->front = delKeyInList(q->front,q->front->key);
    if (q->front == NULL) {
        q->rear = NULL;
    }

    return value;
}


/**
 * @brief Returns the value of the front node but doesn't modify the queue
 *
 * @param q The queue to get the front value.
 * @return The value of the front node.
 */
int queueGetFrontValue(Queue q) {
    if (isQueueEmpty(q)) {
        printf("Error: queue is empty\n");
        exit(1);
    }

    return q.front->value;
}
