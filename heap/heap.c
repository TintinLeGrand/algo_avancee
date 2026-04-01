#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * @brief Helper function to swap two elements in the heap.
 * @param h A pointer to the Heap data structure.
 * @param i The index of the first element.
 * @param j The index of the second element.
 */
void swap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}


/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {
    if(n<=0)
        return NULL;

    Heap *h = malloc(sizeof(Heap));
    h->n = n;
    h->nbElements = 0;
    h->position = malloc(n * sizeof(int));
    h->heap = malloc(n * sizeof(int));
    h->priority = malloc(n * sizeof(double));
    for(int i = 0; i<n;i++){
        h->position[i] = -1;
        h->priority[i] = -1;
    }
    return h;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap h) {
    int i;
    printf("\nn: %d\n", h.n);
    printf("nbElements: %d\n", h.nbElements);
    printf("position: [");
    for (i = 0; i < h.n; i++) {
        printf("%d ", h.position[i]);
    }
    printf("]\npriority: [");
    for (i = 0; i < h.n; i++) {
        printf("%.2lf ", h.priority[i]);
    }
    printf("]\nheap: [");
    for (i = 0; i < h.nbElements; i++) {
        printf("%d ", h.heap[i]);
    }
    printf("]\n");
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority (smallest value in the priority array).
 */
int getElement(Heap h) {
    return h.heap[0];
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority) {
    if(h==NULL)
        return;
    if(element<0 || element >=h->n)
        return;
    if (h->nbElements == h->n) {
        return;
    }

    int i = h->nbElements;
    h->heap[i] = element;
    h->position[element] = i;
    h->priority[element] = priority;
    h->nbElements++;

    while (i > 0 && h->priority[h->heap[i]] < h->priority[h->heap[(i - 1) / 2]]) {
        swap(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority) {
    if(h==NULL)
        return;
    if(element<0 || element>=h->n)
        return;

    if (h->position[element] == -1) {
        insertHeap(h, element, priority);
        return;
    }

    int i = h->position[element];
    h->priority[element] = priority;

    while (i > 0 && h->priority[h->heap[i]] < h->priority[h->heap[(i - 1) / 2]]) {
        swap(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }

    while (2 * i + 1 < h->nbElements) {
        int j = 2 * i + 1;

        if (j + 1 < h->nbElements && h->priority[h->heap[j + 1]] < h->priority[h->heap[j]]) {
            j++;
        }

        if (h->priority[h->heap[i]] <= h->priority[h->heap[j]]) {
            break;
        }

        swap(h, i, j);
        i = j;
    }
}


/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority (smallest value in the priority array)that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
    if(h==NULL || h->nbElements==0){
        printf("Try to remove an element from an empty heap...");
        exit(-1);
    }
    int i;
    int min = h->heap[0];
    h->heap[0] = h->heap[h->nbElements-1];
    h->position[h->heap[h->nbElements-1]] = 0;
    h->nbElements--;
    i = 0;
    while (2 * i + 1 < h->nbElements) {
        int j = 2 * i + 1;

        if (j + 1 < h->nbElements && h->priority[h->heap[j + 1]] < h->priority[h->heap[j]]) {
            j++;
        }

        if (h->priority[h->heap[i]] <= h->priority[h->heap[j]]) {
            break;
        }

        swap(h, i, j);
        i = j;
    }
    h->position[min] = -1;
    return min;
}


