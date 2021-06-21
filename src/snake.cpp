#include "snake.hpp"
#include <math.h>

void Snake::change_dir(Coord2D dir)
{
    if(abs(dir.first) == abs(direction.first) && abs(dir.first) == abs(direction.first))
    {
        return;
    }
    direction = dir;
}

Coord2D Snake::nextPosition()
{
    Coord2D nextPos = head();
    nextPos.first += direction.first;
    nextPos.second += direction.second;
    return nextPos;
}

void Snake::eat(Coord2D food)
{ 
    eatedFood.push_back(food); 
}

bool Snake::digest()
{
    if(eatedFood.size() > 0 && eatedFood.front() == tail())
    {
        eatedFood.pop_front();
        return true;
    }
    return false;
}
Coord2D Snake::move()
{
    Coord2D next = nextPosition();
    body.push_front(next);

    if(digest())
    {
        return noPos;
    }
    else
    {
        Coord2D toRemove = tail();
        body.pop_back();
        return toRemove;
    }
}

const Coord2D Snake::noPos = Coord2D(-1, -1);

