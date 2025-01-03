#include "game.h"
#include "mobile.h"
#include <stdlib.h> /* malloc, free, NULL */

/* Initialize everything that makes up the game: player and locations */
Game *GameInit()
{
    // allocate memory for the game structure
    Game *ret = malloc(sizeof(Game));
    if (ret)
    {
        // creates the player objet
        ret->player = MobileNew("You", "A very dynamic and adventurous young person!");
        // If player creation fails, free the Game strcutre
        if (!ret->player)
        {
            free(ret);
            return NULL;
        }

        // Initialize locations and link the player to the starting location
        Location *startLocation = LocationInit();
        // If location initialization fails, cleans up the player and Game Structure
        if (!startLocation)
        {
            MobileDelete(ret->player);
            free(ret);
            return NULL;
        }

        // To set the player's current loction to the starting location
        ret->player->currentLocation = startLocation;
    }
    return ret;
}

/* correctly deallocate everythig that was dynamically allocated in GameInit */
Game *GameShutdown(Game *g)
{
    if (g)
    {
        g->player = MobileDelete(g->player);
        //Frees up all the locations
        free(g);
    }
    return (Game *)NULL;
}