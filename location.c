#include "location.h"

#include <string.h> /* strdup */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

// Creates a new Location with a name and description
// @param name: the name of the location
// @param desc: the description of the location
// @return a pointer to the newly created Location
// @note all exits are initialized to NULL
extern Location *LocationNew(char *name, char *desc)
{
   Location *loc = (Location *)NULL;
   if (name && desc)
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
   }
   return loc;
}

// Frees all memory associated with a Location
// @param l: the location to be deleted
// @note safely frees name, description, and the location itself
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

// Prints the name and description of a Location
// @param loc: the location to be printed
// @note does nothing if loc is NULL
void LocationPrint(Location *loc)
{
   if (loc)
   {
      printf("Location: %s\n", loc->name);
      printf("Description: %s\n", loc->desc);
   }
}

// Sets an exit from one Location to another
// @param from: the starting location
// @param dir: the direction of the exit
// @param to: the destination location
// @note does nothing if from is NULL or dir is invalid
void LocationSetExit(Location *from, Direction dir, Location *to)
{
   if (from && dir >= 0 && dir < 6)
   {
      from->exits[dir] = to;
   }
}

// Initializes all locations and establishes connections between them
// @return a stack containing all locations
// @note each location is pushed onto the stack in reverse order of creation
Stack *LocationInit()
{
   Location *loc1 = LocationNew("On the road",
                                "You find yourself on a mystical path, surrounded by ethereal flowers that shimmer faintly under the moonlight. "
                                "The gentle rustling of leaves whispers secrets of distant lands, urging you to journey onward.");

   Location *loc2 = LocationNew("On the road",
                                "The road stretches endlessly ahead, flanked by ancient trees whose roots seem to pulse with an otherworldly glow. "
                                "Soft, haunting melodies drift through the air, as though sung by unseen travelers of old.");

   Location *loc3 = LocationNew("On the road",
                                "This stretch of the road feels eerily calm. The flowers here are vibrant, their colors shifting like a living rainbow. "
                                "A faint golden mist swirls at your feet, as if guiding your steps.");

   Location *loc4 = LocationNew("FrontYard",
                                "You stand in a grand courtyard with stone paths that intertwine like a maze. Enchanted lanterns float mid-air, "
                                "casting soft, warm light over a garden brimming with magical herbs and singing roses.");

   Location *loc5 = LocationNew("Entrance",
                                "An imposing archway, carved from ancient stone, marks the gateway to a forgotten realm. Glowing runes pulsate rhythmically, "
                                "their light bathing you in an aura of mystery and power. A faint hum fills the air, vibrating through your very being.");

   Location *loc6 = LocationNew("Dining Room",
                                "A majestic dining hall where the chandeliers sparkle like captured starlight. The table is laden with an eternal feast, "
                                "each dish more enticing than the last, and the aromas are almost too intoxicating to resist.");

   Location *loc7 = LocationNew("Kitchen",
                                "The air buzzes with magical energy in this enchanted kitchen. Cauldrons bubble with unknown brews, and utensils float "
                                "gracefully through the air. The walls are lined with shelves holding spellbound spices and ancient recipes.");

   Location *loc8 = LocationNew("Laundry Room",
                                "A delightful chaos reigns in this whimsical chamber, where tiny sprites dart about, cleaning garments with magical efficiency. "
                                "Soap bubbles float lazily through the room, glowing faintly and humming soft, harmonious tunes.");

   Location *loc9 = LocationNew("Office",
                                "A serene study filled with ancient knowledge. Towering bookshelves hold tomes bound in leather and gold, "
                                "while a grand desk, strewn with parchment and glowing quills, invites you to unravel secrets long forgotten.");

   Location *loc10 = LocationNew("Living Room",
                                 "This cozy living space is alive with magic. A roaring fire flickers in the hearth, its flames dancing to an unheard melody. "
                                 "Chairs and sofas adjust themselves as if welcoming you, and the room feels imbued with a comforting presence.");

   Location *loc11 = LocationNew("Attic",
                                 "The attic is a treasure trove of forgotten wonders. Dust motes float lazily in the golden light streaming through a small window, "
                                 "revealing relics of adventures past: chests, maps, and enchanted artifacts lie scattered, waiting to be rediscovered.");

   Location *loc12 = LocationNew("Cellar",
                                 "The cellar exudes an aura of mystery. Its damp stone walls are lined with shelves holding jars of captured starlight, "
                                 "casting faint, shimmering patterns across the floor. The air is thick with the scent of age and forgotten magic.");

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
   StackPush(stack, loc12);
   StackPush(stack, loc11);
   StackPush(stack, loc10);
   StackPush(stack, loc9);
   StackPush(stack, loc8);
   StackPush(stack, loc7);
   StackPush(stack, loc6);
   StackPush(stack, loc5);
   StackPush(stack, loc4);
   StackPush(stack, loc3);
   StackPush(stack, loc2);
   StackPush(stack, loc1);

   return stack; // Retorne the stack
}

// Frees all locations using a stack
// @param stack: the stack of locations to be freed
// @note frees both the locations and the stack itself
void LocationDestroy(Stack *stack)
{
   while (!StackIsEmpty(stack))
   {
      Location *loc = StackPop(stack); // Remove the top location
      LocationDelete(loc);             // Free the location's memory
   }
   StackDestroy(stack); // Free the stack
}
