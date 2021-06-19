#include "snakegame.hpp"
#include <unistd.h>
void printPos(Coord2D at, char ch = '@') {
    mvaddch(at.first, at.second, ch);
}

std::unordered_map<int, Coord2D> movementDir = 
{
    {KEY_UP, {-1, 0}},
    {KEY_DOWN, {1, 0}},
    {KEY_LEFT, {0, -1}},
    {KEY_RIGHT, {0, 1}}
};

void SnakeGame::init()
{
    Game::init();
    // print boarder;

    std::string row_boarder(gameMap.second, '#');
    std::string row_normal = '#' + std::string(gameMap.second - 2, ' ') + '#';

    for(int row = 0; row < gameMap.first; row++)
    {
        const char* toPrint = (row == 0 || (row + 1) == gameMap.first)?
                                row_boarder.c_str() :
                                row_normal.c_str();
        mvprintw(row + mapOffset.first, 
                    mapOffset.second, 
                    toPrint);
    }
    printPos(snake.head());
}

bool SnakeGame::collision()
{
    return false;
}

void SnakeGame::update()
{
    mvprintw(1, 0, "Map size (Row, Col) = (%d, %d) ofset: (%d, %d)", 
                gameMap.first, gameMap.second,
                mapOffset.first, mapOffset.second);
    if(key != ERR)
    {
        mvprintw(0, 0, "Input: %c", key);
        if(movementDir.find(key) != movementDir.end())
        {
            snake.change_dir(movementDir[key]);
        }
        Coord2D nextPos = snake.nextPosition();
        mvprintw(3, 0, "Next pos: %d %d", nextPos.first, nextPos.second);
        printPos(nextPos);
        nextPos = snake.move();
        if(nextPos != snake.noPos) printPos(nextPos, ' ');
        refresh();
    }
}

