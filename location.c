#include "location.h"
#include "stack.h"
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

/* creation of the locations" */
Location *LocationInit()
{
   Location *loc1 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc2 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc3 = LocationNew("On the road", "You are in a open field with only beautiful flowers around you.");
   Location *loc4 = LocationNew("FrontYard", "A long hallway with doors on both sides.");
   Location *loc5 = LocationNew("Entrance", "The gateway to a mystical world, where ancient runes glow softly on the stone archway.");
   Location *loc6 = LocationNew("Dining Room", "A grand hall with a shimmering crystal chandelier and an enchanted feast eternally laid out on the table.");
   Location *loc7 = LocationNew("Kitchen", "A magical kitchen filled with bubbling cauldrons and floating utensils crafting meals on their own.");
   Location *loc8 = LocationNew("Laundry Room", "A whimsical chamber where clothes are cleaned by tiny, playful sprites.");
   Location *loc9 = LocationNew("Office", "A quiet study lined with ancient tomes and a desk covered in mysterious scrolls.");
   Location *loc10 = LocationNew("Living Room", "A cozy living area with a roaring magical fire and chairs that adjust themselves for comfort.");
   Location *loc11 = LocationNew("Attic", "A dusty attic brimming with forgotten treasures and enchanted relics.");
   Location *loc12 = LocationNew("Cellar", "A dark and cold cellar, with glowing jars containing captured starlight.");

   // Connection
   LocationSetExit(loc1, NORTH, loc2);
   LocationSetExit(loc1, SOUTH, loc3);
   LocationSetExit(loc1, WEST, loc4);

   LocationSetExit(loc2, SOUTH, loc1);
   LocationSetExit(loc2, NORTH, loc2);

   LocationSetExit(loc3, NORTH, loc1);
   LocationSetExit(loc3, SOUTH, loc3);

   LocationSetExit(loc4, WEST, loc5);
   LocationSetExit(loc4, EAST, loc1);

   LocationSetExit(loc5, EAST, loc4);
   LocationSetExit(loc5, NORTH, loc6);
   LocationSetExit(loc5, SOUTH, loc10);
   LocationSetExit(loc5, UP, loc11);
   LocationSetExit(loc5, DOWN, loc12);

   LocationSetExit(loc6, SOUTH, loc5);
   LocationSetExit(loc6, WEST, loc7);

   LocationSetExit(loc7, EAST, loc6);
   LocationSetExit(loc7, SOUTH, loc8);

   LocationSetExit(loc8, NORTH, loc7);
   LocationSetExit(loc8, SOUTH, loc9);

   LocationSetExit(loc9, NORTH, loc8);
   LocationSetExit(loc9, EAST, loc10);

   LocationSetExit(loc10, WEST, loc9);
   LocationSetExit(loc10, NORTH, loc5);

   LocationSetExit(loc11, DOWN, loc5);
   LocationSetExit(loc12, UP, loc5);


   // stacking up all the locations
   Stack *stack = StackCreate();
   StackPush(stack, loc1);
   StackPush(stack, loc2);
   StackPush(stack, loc3);
   StackPush(stack, loc4);
   StackPush(stack, loc5);
   StackPush(stack, loc6);
   StackPush(stack, loc7);
   StackPush(stack, loc8);
   StackPush(stack, loc9);
   StackPush(stack, loc10);
   StackPush(stack, loc11);
   StackPush(stack, loc12);
   
   return stack; // Retorne the first location
}

/* Destroys all locations using the stack */
void LocationDestroy(Stack *stack)
{
   while (!StackIsEmpty(stack))
   {
      Location *loc = StackPop(stack); // Remove the top location
      LocationDelete(loc);             // Free the location's memory
   }
   StackDestroy(stack); // Free the stack
}
