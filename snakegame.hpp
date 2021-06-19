#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include "game.hpp"
typedef std::pair<int, int> Coord2D;

class SnakeGame : public Game
{
    public:
        SnakeGame(Coord2D mapSize, Coord2D mapStartPoint, int fps) : Game(fps), map(mapSize), mapStartPoint(mapStartPoint) {}
        void update();
        void init();
    private:
        // Snake snake;
        Coord2D mapStartPoint;
        Coord2D map;
};


#endif