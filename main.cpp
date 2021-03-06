#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "snakegame.hpp"
// terminal size: (LINES, COLS)
void ncurses_init()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    cbreak();
}
int main()
{
    ncurses_init();
    Coord2D map(LINES/2, COLS/2);

    // Game game(30);
    SnakeGame game(map, 10);
    game.init();
    game.start();


    endwin();
}