#include <stdio.h>
#include <stdlib.h>


#include "stack.h"

/* Creates a new stack */
Stack *StackCreate() {
    Stack *stack = malloc(sizeof(Stack));
    if (stack) {
        stack->top = NULL; // Initialize the stack as empty
    }
    return stack;
}

/* Checks if the stack is empty */
int StackIsEmpty(Stack *stack) {
    return stack->top == NULL;
}

/* Pushes a Location onto the stack */
void StackPush(Stack *stack, Location *location) {
    if (!stack || !location) return;

    // Create a new stack node
    StackNode *node = malloc(sizeof(StackNode));
    if (node) {
        node->location = location;   // Assign the Location to the node
        node->next = stack->top;    // Point the new node to the current top
        stack->top = node;          // Update the stack's top pointer
    }
}

/* Returns the top Location without removing it */
Location *StackHead(Stack *stack) {
    if (!StackIsEmpty(stack)) {
        return stack->top->location; // Return the Location at the top
    }
    return NULL;
}

/* Pops the top Location off the stack */
Location *StackPop(Stack *stack) {
    if (StackIsEmpty(stack)) return NULL;

    StackNode *node = stack->top;       // Get the top node
    Location *location = node->location; // Extract the Location
    stack->top = node->next;            // Move the top pointer down
    free(node);                         // Free the node

    return location;
}

/* Destroys the stack and frees all memory */
void StackDestroy(Stack *stack) {
    while (!StackIsEmpty(stack)) {
        StackPop(stack); // Remove and free each node
    }
    free(stack); // Free the stack structure
}
