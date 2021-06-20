#include "snakemap.hpp"


bool SnakeMap::test(Coord2D pos)
{
    size_t index = getIndex(pos);
    if(mapState.size() < index) return true;
    return mapState[index];
}

void SnakeMap::set(Coord2D pos, bool occupy)
{
    size_t index = getIndex(pos);
    if(mapState.size() < index) return;
    mapState[index] = occupy;
    empty_space += (occupy == true) ? -1 : 1;
}

void SnakeMap::set(std::vector<Coord2D> pos, bool occupy)
{
    for(auto it = pos.begin(); it != pos.end(); it++)
    {
        set((*it), occupy);
    }
}

size_t SnakeMap::getIndex(Coord2D pos)
{
    int r = pos.first - _offset.first;
    int c = pos.second - _offset.second;
    int index = r * col() + c;
    return index;
}

Coord2D SnakeMap::get_center()
{
    return {_offset.first + map.first / 2, _offset.second + map.second / 2};
}