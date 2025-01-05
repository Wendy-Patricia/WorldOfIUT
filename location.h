#ifndef LOCATION_H
#define LOCATION_H


#include "exits.h" // Direction and exits
#include "stack.h"

typedef struct Location {
    char *name;                 // Location name
    char *desc;                 // Description of the location
    struct Location *exits[6];  // Connections in each direction
} Location;

// Function prototypes
Location *LocationNew(char *name, char *desc);
void LocationDelete(Location *l);
void LocationPrint(Location *l);
void LocationSetExit(Location *from, Direction dir, Location *to);

// Stack-related functions
Stack *LocationInit();         // Allocate the new locations
void LocationDestroy(Stack *stack); // Destroy the world

#endif // LOCATION_H
