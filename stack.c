#include "location.h"
#include <stdlib.h>

// Creates a new stack
// @return a pointer to the newly created stack
// @note the stack is initialized as empty
Stack *StackCreate()
{
    Stack *stack = malloc(sizeof(Stack));
    if (stack)
    {
        stack->top = NULL; // Initialize the stack as empty
    }
    return stack;
}

// Checks if the stack is empty
// @param stack: the stack to be checked
// @return 1 if the stack is empty, 0 otherwise
// @note returns 1 if stack->top is NULL
int StackIsEmpty(Stack *stack)
{
    return stack->top == NULL;
}

// Pushes a Location onto the stack
// @param stack: the stack to push onto
// @param location: the Location to be added to the stack
// @note does nothing if stack or location is NULL
void StackPush(Stack *stack, Location *location)
{
    if (!stack || !location)
        return;

    // Create a new stack node
    StackNode *node = malloc(sizeof(StackNode));
    if (node)
    {
        node->location = location; // Assign the Location to the node
        node->next = stack->top;   // Point the new node to the current top
        stack->top = node;         // Update the stack's top pointer
    }
}

// Returns the top Location without removing it
// @param stack: the stack to query
// @return the Location at the top of the stack
// @note returns NULL if the stack is empty
Location *StackHead(Stack *stack)
{
    if (!StackIsEmpty(stack))
    {
        return stack->top->location; // Return the Location at the top
    }
    return NULL;
}

// Pops the top Location off the stack
// @param stack: the stack to pop from
// @return the Location that was removed from the stack
// @note returns NULL if the stack is empty
Location *StackPop(Stack *stack)
{
    if (StackIsEmpty(stack))
        return NULL;

    StackNode *node = stack->top;        // Get the top node
    Location *location = node->location; // Extract the Location
    stack->top = node->next;             // Move the top pointer down
    free(node);                          // Free the node

    return location;
}

// Destroys the stack and frees all memory
// @param stack: the stack to be destroyed
// @note frees all nodes and the stack structure itself
void StackDestroy(Stack *stack)
{
    while (!StackIsEmpty(stack))
    {
        StackPop(stack); // Remove and free each node
    }
    free(stack); // Free the stack structure
}
