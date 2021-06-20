#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include <unordered_map>
#include <vector>
#include <ncurses.h>
#include "snake.hpp"
#include "game.hpp"
#include "snakemap.hpp"

#define FOOD 'o'
#define WALL '#'
#define SNAKE_BODY '*'
#define SNAKE_HEAD '@'
#define SNAKE_TAIL '-'

extern std::unordered_map<int, Coord2D> movementDir;

class SnakeGame;

class SnakeInitState : public StateBase {
    public:
        SnakeInitState(SnakeGame *game);
        void onStateEnter();
        void update();
        void onStateExit() {}

    protected:
        SnakeGame *s_game;
};

class SnakePlayState : public SnakeInitState {
    public: 
        SnakePlayState(SnakeGame *game) : SnakeInitState(game) {}
        void onStateEnter();
        void update();
        void onStateExit(){}
};


class SnakeGame : public Game
{
    friend class SnakeInitState;
    friend class SnakePlayState;

    public:
        SnakeGame(Coord2D mapSize, int fps) : 
            Game(fps),
            snakemap(mapSize, {(LINES - mapSize.first)/2, 
                                (COLS - mapSize.second) / 2}),
            snake(snakemap.get_center(),
                  movementDir[KEY_RIGHT]) 
            {
            }

        void update();
        void init();

        bool collision();
        Coord2D generate_food();

        void control_snake(int key);
        bool move_snake(Coord2D &newHead, Coord2D &oldHead, Coord2D &toRemove);

        void print_map();
        void print_allSnake();
        void print_updatedSnake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove);

        void reset() { snakemap.reset(); snake.reset(snakemap.get_center(), movementDir[KEY_RIGHT]); }

    private:
        SnakeMap snakemap;
        std::vector<bool> mapInfo;
        Snake snake;
};


#endif