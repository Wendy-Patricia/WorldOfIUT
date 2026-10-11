#include "ui.h"
#include "cmd.h"

#include <ncurses.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

static void UiShowStatus(Game *g, const char *status)
{
    clear();
    box(stdscr, 0, 0);

    mvprintw(1, 2, "=== World of IUT ===");

    if (g && g->player && g->player->currentLocation)
    {
        mvprintw(3, 2, "Player: %s", g->player->name);
        mvprintw(4, 2, "Location: %s", g->player->currentLocation->name);
        mvprintw(6, 2, "%s", g->player->currentLocation->desc);

        mvprintw(12, 2, "Exits:");
        int count = 0;
        for (int i = NORTH; i <= DOWN; ++i)
        {
            if (g->player->currentLocation->exits[i])
            {
                if (count > 0)
                    printw(",");
                printw(" %s", dirtostr(i));
                count++;
            }
        }
        if (count == 0)
            printw(" none");
    }
    else
    {
        mvprintw(3, 2, "Game not initialized.");
    }

    mvprintw(LINES - 5, 2, "Command: ");
    if (status && status[0] != '\0')
    {
        mvprintw(LINES - 7, 2, "%s", status);
    }

    mvprintw(LINES - 2, 2, "Commands: help, look around, go north, quit");
    refresh();
}

void UiRunGame(Game *g)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    }

    char command[128];
    char status[256] = "Welcome to World of IUT!";

    while (1)
    {
        UiShowStatus(g, status);
        echo();
        mvgetnstr(LINES - 5, 12, command, sizeof(command) - 1);
        noecho();

        if (strcmp(command, "") == 0)
            continue;

        strncpy(status, command, sizeof(status) - 1);
        status[sizeof(status) - 1] = '\0';

        parseAndExecute(command, g);

        if (strcasecmp(command, "quit") == 0)
            break;
    }

    endwin();
}
