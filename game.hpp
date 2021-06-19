#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <iostream>

double get_current_ms_clock();

enum GameState
{
    Idle,
    Run,
    Pause,
    End
};


class Game
{
    public:
        virtual void get_input();
        virtual void update();
        virtual bool should_update();
        virtual void init();
        virtual void start();
        // virtual void pause();
        virtual void update_timer();
        virtual void print_fps(int y = 1, int x = 0) { mvprintw(y, x, "Frame: %5d", frame); };
        Game(int fps) : fps(fps), key(ERR), frame(0), timeCounter(0), ms_perFrame(1000.0/fps), state(Idle) {}
    private:
        int fps;
        int key;
        int frame;
        double timeCounter;
        double ms_perFrame;
        double lastUpdateClock;
        GameState state;
};


#endif