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


void SnakeGame::init()
{
    setState(new SnakeInitState(this));
}

void SnakeGame::control_snake(int key)
{
    if(movementDir.find(key) != movementDir.end())
    {
        snake.change_dir(movementDir[key]);
    }
}

bool SnakeGame::collision()
{
    return false;
}

void SnakeGame::print_map()
{
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
    mvprintw(1, 0, "Map size (Row, Col) = (%d, %d) ofset: (%d, %d)", 
                gameMap.first, gameMap.second,
                mapOffset.first, mapOffset.second);
}

bool SnakeGame::move_snake(Coord2D &newHead, Coord2D &oldHead, Coord2D &toRemove)
{
    newHead = snake.nextPosition();

    // check collision

    oldHead = snake.head();
    toRemove = snake.move();

    return true;
}

void SnakeGame::print_snake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove)
{
    printPos(newHead, '*');
    printPos(oldHead);
    if(toRemove != snake.noPos) printPos(toRemove, ' ');
}

SnakeInitState::SnakeInitState(SnakeGame *game) : 
    StateBase(game), s_game(game) { }




void SnakeInitState::onStateEnter()
{
    mvprintw(0, 0, "Press 's' to start");
    s_game->print_map();
    refresh();
}

void SnakeInitState::update()
{
    if(s_game->currentKey() == 's')
    {
        s_game->setState(new SnakePlayState(s_game));
    }
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
        }   

        s_game->control_snake(key);

        Coord2D newHead, oldHead, toRemove;
        bool validMove = s_game->move_snake(newHead, oldHead, toRemove);
        
        if(validMove == false)
        {

        }
        
        s_game->print_snake(newHead, oldHead, toRemove);
        refresh();
    
        s_game->update_frame();
    }
}

