#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

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
        SnakeGame(Coord2D mapSize, Coord2D mapStartPoint, int fps) : 
            Game(fps), gameMap(mapSize), mapOffset(mapStartPoint),
                snake(getMapCenter(),
                    movementDir[KEY_RIGHT]) 
                    {
                    }
        void update();
        void init();
        bool collision();
        Coord2D getMapCenter() 
        {
            return {mapOffset.first + gameMap.first / 2, mapOffset.second + gameMap.second / 2};
        }
    private:
        Coord2D gameMap;
        Coord2D mapOffset;
        Snake snake;
};


#endif