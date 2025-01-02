#ifndef LOCATION_H
#define LOCATION_H


typedef struct 
{
    char *name;
    char *desc;
} Location;

extern Location *LocationNew(char *name, char *desc);
extern void LocationDelete(Location *l);
extern void LocationPrint(Location *l);


#endif // LOCATION_H