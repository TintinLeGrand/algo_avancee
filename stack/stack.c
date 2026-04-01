/**
 * @file stack.c
 * @brief Implementation file for the Stack data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../list/list.h"

/**
 * @brief Creates a new stack with no elements.
 *
 * @return A pointer to the new stack.
 */
Stack* createStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    *stack = newList();
    return stack;
}

/**
 * @brief Pushes an element onto the top of the stack.
 *
 * @param stack The stack to push onto.
 * @param data The data to push onto the stack.
 */
void push(Stack* stack, int data) {
    *stack = addKeyValueInList(*stack,NULL,data);
}

/**
 * @brief Pops an element from the top of the stack.
 *
 * @param stack The stack to pop from.
 *
 * @return The data from the top element of the stack.
 */
int pop(Stack* stack) {

    if (stack == NULL) {
        printf("Error: null pointer for stack...\n");
        exit(EXIT_FAILURE);
    }
    if (*stack == NULL) { //empty list/stack
        printf("Error: stack is empty\n");
        exit(EXIT_FAILURE);
    }

    int data = (*stack)->value;
    *stack = delKeyInList(*stack,(*stack)->key);

    return data;
}

/**
 * @brief Peeks at the top element of the stack without removing it.
 *
 * @param stack The stack to peek at.
 *
 * @return The data from the top element of the stack.
 */
int peek(Stack stack) {
    if (stack == NULL) {
        printf("Error: stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return stack->value;
}

/**
 * @brief Checks whether the stack is empty.
 *
 * @param stack The stack to check.
 *
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isStackEmpty(Stack stack) {
    return stack == NULL;
}

/**
 * @brief Prints the contents of the stack to stdout.
 *
 * @param stack The stack to print.
 */
void stackPrint(Stack stack) {
    printList(stack,0);
}
