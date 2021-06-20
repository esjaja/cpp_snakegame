#ifndef _SNAKE_MAP_H
#define _SNAKE_MAP_H

#include <vector>
#include "snake.hpp"

class SnakeMap
{
    public:
        SnakeMap(Coord2D mapSize, Coord2D mapOffset): 
            map(mapSize), _offset(mapOffset)
        {
            mapState.resize(row() * col());
            empty_space = mapState.size();
        }
        bool test(Coord2D pos);
        void set(Coord2D pos, bool occupy);
        void set(std::vector<Coord2D> pos, bool occupy);

        size_t getIndex(Coord2D pos);

        Coord2D get_center();
        Coord2D get_map() { return map; }
        Coord2D get_offset() { return _offset; }

        int row() { return map.first; }
        int col() { return map.second; }
    private:
        Coord2D map;
        Coord2D _offset;
        std::vector<bool> mapState;
        int empty_space;
};


#endif