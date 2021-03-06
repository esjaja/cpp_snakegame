#ifndef _SNAKE_H
#define _SNAKE_H

#include <ncurses.h>
#include <deque>
#include <vector>
typedef std::pair<int, int> Coord2D;

class Snake
{
    public:
        void eat(Coord2D food);
        bool digest();
        Coord2D nextPosition();
        Coord2D move();

        void reset(Coord2D initPos, Coord2D dir)
        {
            body.clear();
            eatedFood.clear();
            body.push_front(initPos);
            direction = dir;
        }
        void change_dir(Coord2D dir);

        Coord2D head() { return body.front(); }
        Coord2D tail() { return body.back(); }
        size_t length() { return body.size(); }
        
        std::vector<Coord2D> get_allpos()
        {
            return std::vector<Coord2D>(body.begin(), body.end());
        }

        Snake(Coord2D initPos, Coord2D dir) : direction(dir) { 
            reset(initPos, dir);
        }



        static const Coord2D noPos;
    private:
        std::deque<Coord2D> body;
        std::deque<Coord2D> eatedFood;
        Coord2D direction;
};

#endif