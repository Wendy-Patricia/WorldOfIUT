#ifndef MOBILE_H
#define MOBILE_H
#include "location.h"

typedef struct 
{
    char *name;
    char *desc;
    Location *currentLocation; // New field to track player's current location
} Mobile;

void MobileMove(Mobile *m, Location *newLocation);
extern Mobile *MobileNew(char *name, char *desc);
extern Mobile *MobileDelete(Mobile *m);
extern void MobilePrint(Mobile *m);
#endif // MOBILE_H