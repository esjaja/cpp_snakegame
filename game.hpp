#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <iostream>

double get_current_ms_clock();

class Game;
class StateBase
{
    public:
        StateBase(Game *_game)  { game = _game; }
        virtual void onStateEnter() = 0;
        virtual void update() = 0;
        virtual void onStateExit() = 0;
        virtual ~StateBase() = default;
    protected:
        Game *game;
};

class Game
{
    public:
        void get_input();
        int currentKey() { return key; }

        void update_timer();
        bool should_update();
        void update_frame() { ms_timeCounter = 0; frame++; }
        void set_fps(int _fps);
        
        void setState(StateBase *state);

        virtual void init();
        virtual void start();

        Game(int fps) : key(ERR), frame(0), 
                        ms_timeCounter(0), gameState(nullptr)
                        { 
                            set_fps(fps);
                        }
        virtual ~Game() {}
        StateBase* pauseState;
    private:
        int key;
        int fps;
        int frame;
        double ms_perFrame;
        double ms_timeCounter;
        double lastUpdateClock;
        StateBase* gameState;
};

#endif