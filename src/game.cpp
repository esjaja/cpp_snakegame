#include "game.hpp"

inline
double get_current_ms_clock()
{
    // This measure CPU time, not real elapsed time
    // clock_t ticks = clock();
    // return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;

    struct timeval start;
    gettimeofday(&start, NULL);
    return start.tv_sec * 1000.0 + start.tv_usec / 1000.0;
}

inline
void Game::get_input()
{
    int newKey = getch();
    key = newKey == ERR ? key : newKey;
}


void Game::set_fps(int _fps)
{ 
    fps = _fps; 
    ms_perFrame = 1000.0 / fps; 
}
 

void Game::update_timer()
{
    double current_time = get_current_ms_clock() ;
    double clockPassed = (current_time - lastUpdateClock);
    ms_totalTime += clockPassed;
    ms_timeCounter += clockPassed;
    lastUpdateClock = current_time;
    mvprintw(2,0,"FPS: %d, Frame: %d, Time elapsed: %.2lf sec", fps, frame, ms_totalTime / 1000);
}

void Game::update_frame()
{
    ms_timeCounter = 0; 
    frame++; 
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