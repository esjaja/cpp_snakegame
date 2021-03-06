#include "snakemap.hpp"
#include <time.h>
#include <random>

bool SnakeMap::test(size_t index)
{
    if(mapState.size() < index) return true;
    return mapState[index];
}

bool SnakeMap::test(Coord2D pos)
{
    size_t index = getIndex(pos);
    return test(index);
}

void SnakeMap::set(size_t index, bool occupy)
{
    if(mapState.size() < index) return;
    bool origin = mapState[index];
    mapState[index] = occupy;
    if(origin != occupy)
        empty_space += (occupy == true) ? -1 : 1;
}

void SnakeMap::set(Coord2D pos, bool occupy)
{
    size_t index = getIndex(pos);
    set(index, occupy);
}

void SnakeMap::set(int r, int c, bool occupy)
{
    size_t index = (r * col()) + c;
    set(index, occupy);
}

void SnakeMap::set(std::vector<Coord2D> pos, bool occupy)
{
    for(auto it = pos.begin(); it != pos.end(); it++)
    {
        set((*it), occupy);
    }
}

void SnakeMap::reset() 
{
    srand(time(NULL));
    mapState.clear();
    mapState.resize(row() * col());
    empty_space = mapState.size();
    setWalls();
}

Coord2D SnakeMap::get_empty_pos()
{
    if(empty_space == 0) return Snake::noPos;

    int max = mapState.size() - 1;
    int min = 0;
    int randomIndex = rand() % (max - min + 1) + min;;

    while(test(randomIndex) == true)
    {
        randomIndex = (randomIndex + 1) % (max + 1);
    }
    return toPos(randomIndex);
}

void SnakeMap::setWalls()
{
    int colMax = col();
    int rowMax = row();
    for(int c = 0; c < colMax; c++)
    {
        set(0, c, true);
        set(rowMax - 1, c, true);
    }
    for(int r = 1; r < rowMax; r++)
    {
        set(r, 0, true);
        set(r, colMax - 1, true);
    }
}

size_t SnakeMap::getIndex(Coord2D pos)
{
    int r = pos.first - _offset.first;
    int c = pos.second - _offset.second;
    int index = r * col() + c;
    return index;
}

Coord2D SnakeMap::toPos(size_t index)
{
    int first = (index / col()) + _offset.first;
    int second = (index % col()) + _offset.second;
    return {first, second};
}

Coord2D SnakeMap::get_center()
{
    return {_offset.first + map.first / 2, _offset.second + map.second / 2};
}