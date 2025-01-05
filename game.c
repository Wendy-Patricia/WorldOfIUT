#include "game.h"
#include "mobile.h"
#include <stdio.h>
#include <stdlib.h> 

/* Initialize everything that makes up the game: player and locations */
Game *GameInit() 
{
    // Allocate memory for the game structure
    Game *ret = malloc(sizeof(Game));
    if (!ret)
    {
        printf("Error: Could not allocate memory for the game structure.\n");
        return NULL;
    }

    // Create the player
    ret->player = MobileNew("You", "A young fighter looking for adventures and magic realms!");
    if (!ret->player)
    {
        free(ret); // Free the game structure
        return NULL;
    }

    // Initialize locations and store in the game structure
    ret->locations = LocationInit();
    if (!ret->locations)
    {
        MobileDelete(ret->player); // Free the player
        free(ret);                 // Free the game structure
        return NULL;
    }

    // Set the player's starting location
   ret->player->currentLocation = StackHead(ret->locations);  // Directly assign Location* to the player's current location
    if (!ret->player->currentLocation)
    {
        LocationDestroy(ret->locations); // Free locations
        MobileDelete(ret->player);       // Free the player
        free(ret);                       // Free the game structure
        return NULL;
    }

    
    return ret;
}


/* correctly deallocate everythig that was dynamically allocated in GameInit */
Game *GameShutdown(Game *g)
{
    if (g)
    {
        // Free the player
        MobileDelete(g->player);

        // Free all locations
        LocationDestroy(g->locations);

        // Free the game structure
        free(g);

        printf("Thanks for playing this exciting adventure with us.\n");

        return (Game *)NULL;
    }
}
