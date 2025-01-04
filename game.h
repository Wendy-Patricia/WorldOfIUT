#ifndef GAME_H
#define GAME_H

#include "mobile.h"    // To manage the player
#include "location.h"  // To manage locations
#include "stack.h"     // To manage the stack of locations

typedef struct
{
    Mobile *player;
    Stack *locations;   // Stack to store all locations
} Game;

extern Game *GameInit();
extern void GameShutdown(Game *g);
#endif // GAME_H
