#ifndef STACK_H
#define STACK_H

#include "location.h" // for the manegement of location

typedef struct StackNode {
    Location *location;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;


Stack *StackCreate();
int StackIsEmpty(Stack *stack);
void StackPush(Stack *stack, Location *location);
Location *StackPop(Stack *stack);
Location *StackHead(Stack *stack);
void StackDestroy(Stack *stack);

#endif // STACK_H
