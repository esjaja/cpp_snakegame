#ifndef _SNAKE_GAME_H
#define _SNAKE_GAME_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <ncurses.h>
#include "snake.hpp"
#include "game.hpp"
#include "snakemap.hpp"

#define FOOD 'o'
#define EATEN 'O'
#define WALL '#'
#define SNAKE_BODY '*'
#define SNAKE_HEAD '@'
#define SNAKE_TAIL '-'

#define PER_SCORE_TO_ADD_FPS 5
#define FPS_STEP 2

struct MyHash {
    size_t operator()(const Coord2D & v) const {
        return v.first ^ v.second;
    }
};

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
        void onStateExit();
};


class SnakeGame : public Game
{
    friend class SnakeInitState;
    friend class SnakesetStatePlayState;

    public:
        SnakeGame(Coord2D mapSize, int fps) : 
            Game(fps),
            snakemap(mapSize, 
                    Coord2D((LINES - mapSize.first)/2, 
                            (COLS - mapSize.second) / 2)),
            snake(snakemap.get_center(),
                  movementDir[KEY_RIGHT]), score(0), init_fps(fps)
            {
            }

        void update();
        void init();

        bool collision(const Coord2D& );
        bool at_food(const Coord2D& );
        void eat_food(const Coord2D &);
        void add_score(int value);
        void generate_food();

        bool should_speed_up();
        void speed_up(int);

        void control_snake(int key);
        bool move_snake(Coord2D &newHead, Coord2D &oldHead, Coord2D &toRemove);

        void print_map();
        void print_border();
        void print_allSnake();
        void print_updatedSnake(const Coord2D &newHead, const Coord2D &oldHead, const Coord2D &toRemove);
        void print_allFood();

        void reset() 
        { 
            set_fps(init_fps);
            score = 0;
            food.clear();
            snakemap.reset(); 
            snake.reset(snakemap.get_center(), movementDir[KEY_RIGHT]); 
            snakemap.set(snake.get_allpos(), true);
        }

        size_t foodCount() { return food.size(); }
    private:
        SnakeMap snakemap;
        Snake snake;
        std::unordered_set<Coord2D, MyHash> food;
        int score;
        int init_fps;
};


#endif