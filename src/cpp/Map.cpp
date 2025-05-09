#include "Map.h"

Map::Map(int x_length, int y_length) {
    // set max dimension vector 
    max_dimensions = {x_length, y_length};
    // initialize every tile through first pass




    // initialize neighbours 
}

Map::Map(int x_length, int y_length, int z_length) {
    // set max dimensions vector 
    max_dimensions = { x_length, y_length, z_length };

    std::vector<std::vector<std::vector<Tile>>> graph;
    
    // initialize every tile through first pass
    for (int x = 0; x < max_dimensions[0] ; x++ ){
        for ( int y = 0 ; y < max_dimensions[1] ; y ++ ) {
            for ( int z = 0 ; z < max_dimensions[2] ; z++ ) {
                graph[x][y][z] = new Tile3d(x, y, z)
            }
        }
    }
    



    // initialize neighbours 
}

Map::Map() {

}