#ifndef CMD_H
#define CMD_H
#include "location.h"

#include "game.h" /* for Game structure */
extern void processCommand(Game *g);
extern void parseAndExecute(char *line, Game *game);

#endif // CMD_H

