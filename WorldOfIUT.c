#include <stdio.h> /* for printf in Intro() */
#include "game.h" /* for Game structure and GameInit() */
#include "ui.h" /* for ncurses interface */

void Intro()
{
    printf("Welcome to WorlOfIUT!\n" 
           "Be prepared because you are about to live extraordinary, frightful, yet exciting\n"
           "adventures...\n" 
           "If you're new to the game, you can start by typing 'help'\n" 
           "Farewell, and may the spirit of the Vosges be with you!\n");
}

int main()
{
    Intro();
    Game *g = GameInit();
    if (!g)
    {
        fprintf(stderr, "Failed to initialize the game.\n");
        return 1;
    }

    UiRunGame(g);
    GameShutdown(g);
    return 0;
}
