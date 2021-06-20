#include "snakegame.hpp"
#include <unistd.h>
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

SnakeInitState::SnakeInitState(SnakeGame *game) : 
    StateBase(game), s_game(game) { }


void SnakeInitState::onStateEnter()
{
    std::string row_boarder(s_game->gameMap.second, '#');
    std::string row_normal = '#' + std::string(s_game->gameMap.second - 2, ' ') + '#';
    
    for(int row = 0; row < s_game->gameMap.first; row++)
    {
        const char* toPrint = (row == 0 || (row + 1) == s_game->gameMap.first)?
                                row_boarder.c_str() :
                                row_normal.c_str();
        mvprintw(row + s_game->mapOffset.first, 
                    s_game->mapOffset.second, 
                    toPrint);
    }
    printPos(s_game->snake.head());

    mvprintw(0, 0, "Press 's' to start");

    mvprintw(1, 0, "Map size (Row, Col) = (%d, %d) ofset: (%d, %d)", 
                s_game->gameMap.first, s_game->gameMap.second,
                s_game->mapOffset.first, s_game->mapOffset.second);

    refresh();
}

void SnakeInitState::update()
{
    if(s_game->currentKey() == 's')
    {
        s_game->setState(new SnakePlayState(s_game));
    }
}

void SnakeGame::init()
{
    setState(new SnakeInitState(this));
}

bool SnakeGame::collision()
{
    return false;
}

void SnakePlayState::onStateEnter()
{
    nodelay(stdscr, TRUE);
    mvprintw(0, 0, std::string(COLS, ' ').c_str());
}

void SnakePlayState::update()
{
    if(s_game->should_update()){
        int key = s_game->currentKey();
        if(key != ERR)
        {
            mvprintw(0, 0, "Input: %c", key );
            if(movementDir.find(key) != movementDir.end())
            {
                s_game->snake.change_dir(movementDir[key]);
            }
            Coord2D nextPos = s_game->snake.nextPosition();
            mvprintw(3, 0, "Next pos: %d %d", nextPos.first, nextPos.second);
            printPos(nextPos, '*');
            printPos(s_game->snake.head());
            // sleep(1);
            nextPos = s_game->snake.move();
            if(nextPos != s_game->snake.noPos) printPos(nextPos, ' ');
            refresh();
        }
        s_game->add_frameCounter();
    }
}

