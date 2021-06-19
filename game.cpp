#include "game.hpp"

double get_current_ms_clock()
{
    clock_t ticks = clock();
    return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

void Game::get_input()
{
    int newKey = getch();
    key = newKey == ERR ? key : newKey;
}

void Game::update()
{
    if(key != ERR){
        mvprintw(0, 0, "Input: %c", key);
        refresh();
    }
}

void Game::update_timer()
{
    double clockPassed = get_current_ms_clock();
    timeCounter += (clockPassed - lastUpdateClock);
    lastUpdateClock = clockPassed;
}

bool Game::should_update()
{
    return timeCounter >= ms_perFrame;
}

void Game::init()
{
    frame = 0;
    timeCounter = 0;
    key = ERR;
    clear();
}

void Game::start()
{
    lastUpdateClock = get_current_ms_clock();
    while(1)
    {
        update_timer();
        get_input();
        if(should_update())
        {
            update();
            timeCounter = 0;
            frame++;
        }

    }
}