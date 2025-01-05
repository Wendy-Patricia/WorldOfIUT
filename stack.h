#ifndef STACK_H
#define STACK_H

// Forward declaration of Location
struct Location; // Informs the compiler that Location is a struct

typedef struct StackNode
{
    struct Location *location; // Use forward-declared Location
    struct StackNode *next;
} StackNode;

typedef struct
{
    StackNode *top; // Pointer to the top of the stack
} Stack;

// Function prototypes
Stack *StackCreate();
int StackIsEmpty(Stack *stack);
void StackPush(Stack *stack, struct Location *location); // Use forward-declared Location
struct Location *StackPop(Stack *stack);
struct Location *StackHead(Stack *stack);

#endif // STACK_H
