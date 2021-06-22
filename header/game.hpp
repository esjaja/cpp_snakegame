#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <iostream>
#include <sys/time.h>

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
        void update_frame();
        void set_fps(int _fps);
        int get_fps() { return fps;}
        
        void set_state(StateBase *state);
        void set_input_block(bool setBlock);
        bool is_input_block();

        virtual void init();
        virtual void start();

        Game(int fps) : key(ERR), frame(0), 
                        ms_timeCounter(0), 
                        ms_totalTime(0),
                        gameState(nullptr),
                        input_block_mode(true)
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
        double ms_totalTime;

        bool input_block_mode;

        StateBase* gameState;
};

#endif