#include "snakegame.hpp"

void SnakeGame::init()
{
    // print boarder;

    std::string row_boarder(map.second, '#');
    std::string row_normal = '#' + std::string(map.second - 2, ' ') + '#';

    for(int row = 0; row < map.first; row++)
    {
        const char* toPrint = (row == 0 || (row + 1) == map.first)?
                                row_boarder.c_str() :
                                row_normal.c_str();
        mvprintw(row + mapStartPoint.first, 
                    mapStartPoint.second, 
                    toPrint);
    }
}



void SnakeGame::update()
{
    mvprintw(1, 0, "Map size (Row, Col) = (%d, %d)", map.first, map.second);
    Game::update();
}

