#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tile.h"
#include "Query.h"


/* 
Other options to consider
 - range ( if not set to dynamic *see Tile_h.md)
*/
class Map {
    public : 
        // graph here 
        std::vector<int> max_dimensions;


        virtual Tile* query(Query::Type type);

        Map(int x_length, int y_length);
        Map(int x_length, int y_length, int z_length);
        Map();
};

#endif