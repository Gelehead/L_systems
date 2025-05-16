#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tile.h"
#include "Query.h"


/* 
Other options to consider
 - range ( if not set to dynamic *see Tile_h.md )
*/
class Map {
    public : 
    std::vector<std::vector<std::vector<Tile>>> graph;
    std::vector<int> max_dimensions;

        std::vector<Tile3d*> get_neighours(int x, int y, int z);
        std::vector<Tile2d*> get_neighours(int x, int y);

        Tile* query(Query::Type type);

        Map(int x_length, int y_length);
        Map(int x_length, int y_length, int z_length);
        Map();
};

#endif