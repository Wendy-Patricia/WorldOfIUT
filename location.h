#ifndef LOCATION_H
#define LOCATION_H
#include "exits.h"




typedef struct Location
{
    char *name;
    char *desc;
    struct Location*exits[6]; //for each direction(north, south, east, west, up and down)
} Location;

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


extern Location *LocationNew(char *name, char *desc);
extern void LocationDelete(Location *l);
extern void LocationPrint(Location *l);
void LocationSetExit(Location *from, Direction dir, Location *to);
Stack *LocationInit();//allocate the new locationd
void LocationDestroy(Stack *stack);//destroy the world


#endif // LOCATION_H