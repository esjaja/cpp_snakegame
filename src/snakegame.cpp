#include "snakegame.hpp"
#include <unistd.h>
#include <vector>




void printPos(Coord2D at, char ch = SNAKE_BODY) {
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
    Coord2D gameMap = snakemap.get_map();
    Coord2D mapOffset = snakemap.get_offset();

    std::string row_boarder(gameMap.second, WALL);
    std::string row_normal = WALL + std::string(gameMap.second - 2, ' ') + WALL;
    
    for(int r_index = 0; r_index < gameMap.first; r_index++)
    {
        const char* toPrint = (r_index == 0 || (r_index + 1) == gameMap.first)?
                                row_boarder.c_str() :
                                row_normal.c_str();
        mvprintw(r_index + mapOffset.first, 
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
    if(food.find(newHead) != food.end())
    {
        snake.eat(newHead);
        food.erase(newHead);
        snakemap.set(newHead, false);
        score++;
        if(((get_fps() - init_fps)/FPS_STEP) * PER_SCORE_TO_ADD_FPS + (PER_SCORE_TO_ADD_FPS - 1) < score)
        {
            set_fps(get_fps() + FPS_STEP);
        }
        mvprintw(4, 0, "Score: %d", score);
    }
    else if(snakemap.test(newHead) == true)
    {
        mvprintw(4, 0, "Invalid: %d, %d", newHead.first, newHead.second);
        return false;
    }

    oldHead = snake.head();
    toRemove = snake.move();

    snakemap.set(newHead, true);
    snakemap.set(toRemove, false);

    return true;
}

void SnakeGame::print_allSnake()
{
    std::vector<Coord2D> ss = snake.get_allpos();
    if(ss.begin() != ss.end()) printPos(*(ss.begin()), SNAKE_HEAD);
    for(auto it = ss.begin() + 1; it != ss.end(); it++)
    {
        printPos(*it, SNAKE_BODY);
    }
}

void SnakeGame::print_updatedSnake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove)
{
    char head = (foodCount() == 0) ? EATEN : SNAKE_BODY;
    printPos(newHead, SNAKE_HEAD);
    printPos(oldHead, head);
    if(toRemove != snake.noPos) printPos(toRemove, ' ');
}

void SnakeGame::generate_food()
{
    Coord2D pos = snakemap.get_empty_pos();
    food.insert(pos);
    snakemap.set(pos, true);
    printPos(pos, FOOD);
}

SnakeInitState::SnakeInitState(SnakeGame *game) : 
    StateBase(game), s_game(game) { }




void SnakeInitState::onStateEnter()
{
    clear();
    nodelay(stdscr, FALSE);
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
    s_game->reset();
    nodelay(stdscr, TRUE);
    
    mvprintw(0, 0, std::string(COLS, ' ').c_str());
}

void SnakePlayState::onStateExit()
{
    nodelay(stdscr, FALSE);
    mvprintw(4, 0, "GGG, Press any key");
    refresh();
    sleep(1);
    getch();
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
            s_game->setState(new SnakeInitState(s_game));
            return;
        }
        s_game->print_updatedSnake(newHead, oldHead, toRemove);

        if (s_game->foodCount() == 0)
        {
            s_game->generate_food();
        }
        
        refresh();
    
        s_game->update_frame();
    }
}
