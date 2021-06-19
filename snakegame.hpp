#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include "snake.hpp"
#include "game.hpp"

extern std::unordered_map<int, Coord2D> movementDir;

class SnakeGame : public Game
{
    public:
        SnakeGame(Coord2D mapSize, Coord2D mapStartPoint, int fps) : 
            Game(fps),
            snake({mapStartPoint.first + mapSize.first / 2, 
                    mapStartPoint.second + mapSize.second/2}, movementDir[KEY_RIGHT]) 
                    {
                        gameMap = mapSize;
                        mapOffset = mapStartPoint;
                    }
        void update();
        void init();
        bool collision();
    private:
        Coord2D gameMap;
        Coord2D mapOffset;
        Snake snake;
};


#endif