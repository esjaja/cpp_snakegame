#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <unordered_map>
#include <deque>
#include <string>
// terminal size: (LINES, COLS)

class Game;
class Snake;
class SnakeGame;


typedef std::pair<int, int> Coord2D;

enum GameState
{
    Idle,
    Run,
    Pause,
    End
};

double get_current_ms_clock()
{
    clock_t ticks = clock();
    return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

class Game
{
    public:
        virtual void get_input();
        virtual void update();
        virtual bool should_update();
        virtual void start();
        // virtual void pause();
        virtual void update_timer();
        virtual void print_fps(int y = 1, int x = 0) { mvprintw(y, x, "Frame: %10d", frame); };
        Game(int fps) : fps(fps), key(ERR), frame(0), timeCounter(0), ms_perFrame(1000.0/fps), state(Idle) {}
    private:
        int fps;
        int key;
        int frame;
        double timeCounter;
        double ms_perFrame;
        double lastUpdateClock;
        GameState state;
};

void Game::get_input()
{
    int newKey = getch();
    key = newKey == ERR ? key : newKey;
}

void Game::update()
{
    if(key != ERR){
        mvprintw(0, 0, "Input: %c", key);
        refresh();
    }
    timeCounter = 0;
    frame++;
}

void Game::update_timer()
{
    double clockPassed = get_current_ms_clock();
    timeCounter += (clockPassed - lastUpdateClock);
    lastUpdateClock = clockPassed;
}

bool Game::should_update()
{
    return timeCounter >= ms_perFrame;
}

void Game::start()
{
    lastUpdateClock = get_current_ms_clock();
    while(1)
    {
        update_timer();
        get_input();
        if(should_update())
        {
            update();
        }

    }
}


class SnakeGame : public Game
{
    public:
        SnakeGame(Coord2D mapSize, int fps) : Game(fps), map(mapSize) {}
        void update();

    private:
        // Snake snake;
        Coord2D map;
};

void ncurses_init()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    cbreak();
}

void SnakeGame::update()
{
    Game::update();
}

int main()
{
    ncurses_init();
    Coord2D map(LINES, COLS);
    SnakeGame game(map, 30);
    game.start();


    endwin();
}