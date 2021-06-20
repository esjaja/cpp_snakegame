#include "game.hpp"

inline
double get_current_ms_clock()
{
    clock_t ticks = clock();
    return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

inline
void Game::get_input()
{
    int newKey = getch();
    key = newKey == ERR ? key : newKey;
}


void Game::set_fps(int _fps)
{ fps = _fps; ms_perFrame = 1000.0 / fps; }
 

void Game::update_timer()
{
    double clockPassed = get_current_ms_clock();
    ms_timeCounter += (clockPassed - lastUpdateClock);
    lastUpdateClock = clockPassed;
    mvprintw(2,0,"FPS: %d, Time elapsed: %.2lf", fps, ms_timeCounter);
}

bool Game::should_update()
{
    return ms_timeCounter >= ms_perFrame;
}

void Game::setState(StateBase *state)
{
    if(gameState){
        gameState->onStateExit(); 
        delete gameState;
    }
    gameState = state; 
    gameState->onStateEnter(); 
}

void Game::init()
{
}

void Game::start()
{
    if(gameState == nullptr)
    {
        mvprintw(0, 0, "Error: no gameState loaded! Press any key to exit");
        nodelay(stdscr, FALSE);
        getch();
        exit(EXIT_FAILURE);
    }
    lastUpdateClock = get_current_ms_clock();
    while(1)
    {
        update_timer();
        get_input();
        gameState->update();
    }
}