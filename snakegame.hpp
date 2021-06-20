#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include <ncurses.h>
#include "snake.hpp"
#include "game.hpp"

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
            Game(fps), gameMap(mapSize), mapOffset({(LINES - mapSize.first)/2, (COLS - mapSize.second) / 2}),
                snake(getMapCenter(gameMap, mapOffset),
                    movementDir[KEY_RIGHT]) 
                    {
                    }
        void update();
        void init();
        bool collision();
        void control_snake(int key);
        void print_map();
        bool move_snake(Coord2D &newHead, Coord2D &oldHead, Coord2D &toRemove);
        void print_snake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove);
        Coord2D getMapCenter(Coord2D mapSize, Coord2D mapOffset) 
        {
            return {mapOffset.first + mapSize.first / 2, mapOffset.second + mapSize.second / 2};
        }
    private:
        Coord2D gameMap;
        Coord2D mapOffset;
        Snake snake;
};


#endif