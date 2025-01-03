#ifndef LOCATION_H
#define LOCATION_H
#include "exits.h"


typedef struct 
{
    char *name;
    char *desc;
    Location*exits[6]; //for each direction(north, south, east, west, up and down)
} Location;

extern Location *LocationNew(char *name, char *desc);
extern void LocationDelete(Location *l);
extern void LocationPrint(Location *l);
void LocationSetExit(Location *from, Direction dir, Location *to);
Location *LocationInit();//allocate the new locationd
void LocationDestroy(Location *start);//destroy the world


#endif // LOCATION_H