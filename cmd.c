#include "cmd.h"
#include "mobile.h"  /* Mobile type for player management */
#include "exits.h"   /* getDir and DIRECTION type */
#include <string.h>  /* strtok, strlen */
#include <strings.h> /* strcasecmp */
#include <stdio.h>   /* printf and stdin */
#include <stdlib.h>  /* exit and free */

static const char prompt[] = "-->";
static const char sep[] = "     \n";

/* react to command "help": print the help message and return */
void cmdHelp()
{
    printf(
        "General help\n"
        "To play, just enter commands after the prompt '-->'\n"
        "Available commands are:\n"
        "- help:         to get this help\n"
        "- quit:         to quit this game\n"
        "- look <where>: to look at places, objects, etc. Use 'look around' to look at the\n"
        "                current room, 'look me' to have a look at yourselves, and\n"
        "                'look <dir>' to look in the given direction (e.g. 'look east' to\n"
        "                look east from the current room). Allowed directions are north, east,\n"
        "                south, west, up, and down.\n"
        "- go <dir>:     to go in the given direction.\n"
        );
}

/* react to command "quit": properly shuts the game down using GameShutdown and exit */
void cmdQuit(Game *game)
{
    game = GameShutdown(game);
    exit(0);
}

/*
    react to command "look". What to look is provided by args. It may be:
    - me: have a look at yourselvesvoid cmdLook(Game *game, char *args)
    - around: look at the place you're in
    - <direction>: take a peek in the given direction
    - else just print "You look at <args>"
 */
void cmdLook(Game *game, char *args) 
{
    if (!args || strlen(args) == 0)
    {
        printf("You must tell what to look (cf 'Help')\n");
        return;
    }

    Mobile *player = game->player;

    // Handle "look me"
    if (!strcasecmp(args, "me"))
    {
        MobilePrint(player);
    }
    // Handle "look around"
    else if (!strcasecmp(args, "around"))
    {
        if (player->currentLocation)
        {
            LocationPrint(player->currentLocation);
        }
        else
        {
            printf("You are nowhere! You (God) should create some locations...\n");
        }
    }
    // Handle "look <direction>"
    else
    {
        Direction dir = strtodir(args); // Convert the string to a Direction
        if (dir == WRONGDIR) // If the direction is invalid
        {
            printf("Invalid direction: %s. Try north, east, south, west, up, or down.\n", args);
        }
        else if (player->currentLocation && player->currentLocation->exits[dir])
        {
            Location *nextLocation = player->currentLocation->exits[dir];
            printf("You look %s and see:\n", args);
            LocationPrint(nextLocation);
        }
        else
        {
            printf("You look %s, but there is nothing in that direction.\n", args);
        }
    }
}



/* react to command "go". The direction to move in is given by args */
void cmdGo(Game *game, char *args)
{
    // Check if the player provided a direction argument
    if (!args || strlen(args) == 0)
    {
        printf("You must provide a direction to go to (cf 'Help').\n");
        return;
    }

    // Ensure the game and player are properly initialized
    if (!game || !game->player || !game->player->currentLocation)
    {
        printf("Error: The game is not properly initialized or you are not in a location.\n");
        return;
    }

    // Retrieve the player and convert the argument into a Direction enum
    Mobile *player = game->player;
    Direction dir = strtodir(args);

    // Check if the direction is invalid
    if (dir == WRONGDIR)
    {
        printf("You cannot go %s.\n", args);
        return;
    }

    // Check if there is an exit in the specified direction
    if (player->currentLocation->exits[dir])
    {
        // Move the player to the new location
        MobileMove(player, player->currentLocation->exits[dir]);
        printf("You move %s.\n", args);

        // Display information about the new location
        LocationPrint(player->currentLocation);
    }
    else
    {
        // No exit in the specified direction
        printf("You try to go %s, but you cannot go %s from here.\n", args, args);
    }
}

/*
    read a line from standard input and return it.
    The returned string was allocated using malloc and free must be called for deallocation
*/
char *getInput()
{
    char *line = NULL;
    size_t linecap = 0;
    printf("%s ", prompt);           /* print the prompt before reading the line */
    getline(&line, &linecap, stdin); /* allocates line, which will have to be freed */
    return line;
}

/*
    parse the input line in two words: the first word is the command and the second is the argument
    line and game must be non-null pointers for anything to happen
*/
void parseAndExecute(char *line, Game *game)
{
    if (line && game) /* check pointers validity */
    {
        char *name = strtok(line, sep); /* extract first word = command */
        if (name)                       // null pointer if line just contains a return (empty line)
        {
            char *args = strtok(NULL, sep); /* extract the second word = argument. The rest of the line is disregarded */
            /* call the appropriate function, depending on the command */
            if (!strcasecmp(name, "help"))
                cmdHelp(); /* cmd=="help" -> call cmdHelp() */
            else if (!strcasecmp(name, "quit"))
                cmdQuit(game); /* cmd=="quit" -> call cmdQuit(). Also properly shuts the game down */
            else if (!strcasecmp(name, "look"))
                cmdLook(game, args); /* cmd=="look" -> call cmdLook(). args specify where/what to look. game contains the necessary info about stuff to look at */
            else if (!strcasecmp(name, "go"))
                cmdGo(game, args); /* cmd="go" -> call cmdGo(). args specify where to go. game contains info about locations and will update the player's location */
            else
                printf("Command not found. Try 'help'\n");
        }
        else
            printf("Command not found. Try 'help'\n");
    }
}

/* reads a user input command line and process to progress in the game */
void processCommand(Game *g)
{
    char *s = getInput();  /* reads a user input line */
    parseAndExecute(s, g); /* process it, and move in the game */
    if (s)
        free(s); /* deallocate the string from getInput() */
}
