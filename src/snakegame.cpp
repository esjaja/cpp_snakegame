#include "snakegame.hpp"
#include <unistd.h>
#include <vector>

void printPos(Coord2D at, char ch = SNAKE_BODY) {
    mvaddch(at.first, at.second, ch);
}
ChangeDirCommand::ChangeDirCommand(SnakeGame *game, Coord2D dir) : 
    Command(game), dir(dir), originDir(game->current_dir())
    {}

ChangeDirCommand::~ChangeDirCommand() {}

bool ChangeDirCommand::execute()
{
    if(originDir != dir)
    {
        game->change_snake_dir(dir);
    }
    return true;
}

void ChangeDirCommand::undo()
{
    game->change_snake_dir(originDir);
}
MoveCommand::MoveCommand(SnakeGame *game) : Command(game){}
bool MoveCommand::execute()
{
    Coord2D newHead, oldHead, toRemove;
    bool validMove = game->move_snake(newHead, oldHead, toRemove);

    char head = (game->foodCount() == 0) ? EATEN : SNAKE_BODY;
    undo_queue.push({newHead, mvinch(newHead.first, newHead.second)});
    printPos(newHead, SNAKE_HEAD);
    undo_queue.push({oldHead, mvinch(oldHead.first, oldHead.second)});
    printPos(oldHead, head);
    if(toRemove != Snake::noPos) {
        undo_queue.push({toRemove, mvinch(toRemove.first, toRemove.second)});
        printPos(toRemove, ' ');
    }

    if(validMove == false)
    {
        game->setState(new SnakeInitState(game));
        return false;
    }
    return true;
}

void MoveCommand::undo()
{
    int i = 0;
    while(undo_queue.empty() == false)
    {
        std::pair<Coord2D, int> toPrint = undo_queue.top();
        undo_queue.pop();
        mvaddch(toPrint.first.first, toPrint.first.second, toPrint.second);
    }
}

MoveCommand::~MoveCommand(){}

CreateFoodCommand::CreateFoodCommand(SnakeGame *game) : Command(game){}
CreateFoodCommand::~CreateFoodCommand() {}
bool CreateFoodCommand::execute()
{
    if (game->foodCount() == 0)
    {
        Coord2D pos = game->generate_food();
        if(pos != Snake::noPos)
        {
            printPos(pos, FOOD);
        }
        foodPos = pos;
    }
    return true;
}

void CreateFoodCommand::undo()
{
    if(foodPos != Snake::noPos)
    {
        
    }
}


std::unordered_map<int, Coord2D> movementDir = 
{
    {KEY_UP, {-1, 0}},
    {KEY_DOWN, {1, 0}},
    {KEY_LEFT, {0, -1}},
    {KEY_RIGHT, {0, 1}}
};

// ======================== SnakeGame =============================
void SnakeGame::init()
{
    setState(new SnakeInitState(this));
}

Coord2D SnakeGame::generate_food()
{
    Coord2D pos = snakemap.get_empty_pos();
    if(pos != Snake::noPos)
    {
        food.insert(pos);
        snakemap.set(pos, true);
    }
    return pos;
}

void SnakeGame::control_snake(int key)
{
    if(movementDir.find(key) != movementDir.end())
    {
        change_snake_dir(movementDir[key]);
    }
}

void SnakeGame::change_snake_dir(Coord2D dir)
{
    snake.change_dir(dir);
}

bool SnakeGame::move_snake(Coord2D &newHead, Coord2D &oldHead, Coord2D &toRemove)
{
    newHead = snake.nextPosition();
    oldHead = snake.head();
    toRemove = snake.tail();
    // check collision
    if(collision(newHead)) return false;
    toRemove = snake.move();

    snakemap.set(newHead, true);
    snakemap.set(toRemove, false);

    return true;
}

bool SnakeGame::collision(const Coord2D& dest)
{    
    if(at_food(dest))
    {
        eat_food(dest);
        add_score(1);
        if(should_speed_up()) speed_up(1);
        
        print_score(3, 0);

        return false;
    }
    else if(snakemap.test(dest) == true)
    {
        return true;
    }
    return false;
}

bool SnakeGame::at_food(const Coord2D& dest)
{
    return food.find(dest) != food.end();
}

void SnakeGame::eat_food(const Coord2D& dest)
{
    snake.eat(dest);
    food.erase(dest);
    snakemap.set(dest, false);
}

void SnakeGame::add_score(int value)
{
    score += value;
}

bool SnakeGame::should_speed_up()
{
    return ((get_fps() - init_fps)/FPS_STEP * PER_SCORE_TO_ADD_FPS 
            + (PER_SCORE_TO_ADD_FPS - 1)) < score;
}

void SnakeGame::speed_up(int addlevel)
{
    set_fps(get_fps() + addlevel * FPS_STEP);
}

// =========== SnakeGame, print ================
void SnakeGame::print_border()
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
void SnakeGame::print_allSnake()
{
    std::vector<Coord2D> ss = snake.get_allpos();
    if(ss.begin() != ss.end()) printPos(*(ss.begin()), SNAKE_HEAD);
    for(std::vector<Coord2D>::iterator it = ss.begin() + 1; it != ss.end(); it++)
    {
        printPos(*it, SNAKE_BODY);
    }
}

void SnakeGame::print_allFood()
{
    for(const Coord2D &coord : food)
    {
        printPos(coord, FOOD);
    }
}

void SnakeGame::print_map()
{
    print_border();
    print_allSnake();
    print_allFood();
}

void SnakeGame::print_updatedSnake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove)
{
    char head = (foodCount() == 0) ? EATEN : SNAKE_BODY;
    printPos(newHead, SNAKE_HEAD);
    printPos(oldHead, head);
    if(toRemove != snake.noPos) printPos(toRemove, ' ');
}

void SnakeGame::print_score(int r, int c)
{
    mvprintw(r, c, "Score: %d", score);
}


// ===== State Object ====
SnakeInitState::SnakeInitState(SnakeGame *game) : 
    StateBase(game), s_game(game) { }




void SnakeInitState::onStateEnter()
{
    clear();
    s_game->setBlock(true);
    mvprintw(0, 0, "Press 's' to start");
    s_game->print_border();
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
    while(cmd_queue.empty() == false)
    {
        Command *cmd = cmd_queue.back();
        cmd_queue.pop();
        delete cmd;
    }
    s_game->reset();
    s_game->setBlock(false);
    
    mvprintw(0, 0, std::string(COLS, ' ').c_str());
}

void SnakePlayState::onStateExit()
{
    s_game->setBlock(true);
    mvprintw(4, 0, "GGG, Press any key");
    refresh();
    sleep(1);
    getch();
}

void SnakePlayState::addCommand(Command* cmd)
{
    cmd_queue.push(cmd);
}

void SnakePlayState::executeCommand()
{
    while(cmd_queue.empty() == false)
    {
        Command *cmd = cmd_queue.front();
        cmd_queue.pop();
        bool ok = cmd->execute();
        history.push(cmd);
        if(ok == false) return;
    }
}

void SnakePlayState::update()
{
    int key = s_game->currentKey();
    if(key != ERR)
    {
        mvprintw(0, 0, "Input: %c", key );
    }
    if(s_game->isBlock())
    {
        if(key == 'r')
            s_game->setBlock(false);
        else if(key == 'u')
        {
            if(history.empty() == false){
            Command *his = history.top();
            history.pop();
            his->undo();
            delete his;
            refresh();
            }
        }
    }
    else if(key == 'p')
    {
        s_game->setBlock(true);
    }
    else if(s_game->isBlock() == false)
    {
        addCommand(new ChangeDirCommand(s_game, movementDir[key]));
        addCommand(new MoveCommand(s_game));
        executeCommand();
        // s_game->control_snake(key);

        // Coord2D newHead, oldHead, toRemove;
        // bool validMove = s_game->move_snake(newHead, oldHead, toRemove);
        // s_game->print_updatedSnake(newHead, oldHead, toRemove);

        // if(validMove == false)
        // {
        //     s_game->setState(new SnakeInitState(s_game));
        //     return;
        // }

        refresh();
        s_game->update_frame();
    }
}

