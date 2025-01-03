#include "location.h"
#include <string.h> /* strdup */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

extern Location *LocationNew(char *name, char *desc)
{
   Location *loc = (Location *)NULL;
   if (name && desc) /** && where)**/
   {
      loc = malloc(sizeof(Location));
      if (loc)
      {
         loc->name = strdup(name);
         loc->desc = strdup(desc);
         for (int i = 0; i < 6; i++)
         {
            loc->exits[i] = NULL; // everthing  is inicializated with null with no incial location
         }
      }
      // loc->currentLocation = NULL;
   }
   return loc;
}

extern void LocationDelete(Location *l)
{
   if (l)
   {
      if (l->name)
         free(l->name);
      if (l->desc)
         free(l->desc);
      free(l);
   }
   return (Location *)NULL;
}

void LocationPrint(Location *loc)
{
   if (loc)
   {
      printf("Location: %s\n", loc->name);
      printf("Description: %s\n", loc->desc);
      printf("Exits:\n");
      const char *directions[] = {"NORTH", "EAST", "SOUTH", "WEST", "UP", "DOWN"};
      for (int i = 0; i < 6; i++)
      {
         if (loc->exits[i])
         {
            printf("- %s: %s\n", directions[i], loc->exits[i]->name);
         }
      }
   }
}

/* Define connexion between 2 locations*/
void LocationSetExit(Location *from, Direction dir, Location *to)
{
   if (from && dir >= 0 && dir < 6)
   {
      from->exits[dir] = to;
   }
}

/* creation of location" */
Location *LocationInit()
{
   Location *loc1 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc2 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc3 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc4 = LocationNew("FrontYard", "A long hallway with doors on both sides.");
 

   // Connection
   LocationSetExit(loc1, NORTH, loc2);
   LocationSetExit(loc2, SOUTH, loc1);
   LocationSetExit(loc2, NORTH, loc3);
   LocationSetExit(loc3, SOUTH, loc2);

   return loc1; // Retorne the first location
}


void LocationDestroy(Location *start)
{
   if (!start)
      return;

   Location *visited[100] = {NULL};
   int count = 0;

   visited[count++] = start;

   for (int i = 0; i < count; i++)
   {
      Location *current = visited[i];
      for (int j = 0; j < 6; j++)
      {
         Location *next = current->exits[j];
         if (next && next != start)
         {
            visited[count++] = next;
         }
      }
      LocationDelete(current);
   }
}
