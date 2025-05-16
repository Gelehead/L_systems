#include "Map.h"

Map::Map() {}

Map::Map(int x_length, int y_length) {

    // set max dimension vector 
    max_dimensions = {x_length, y_length};

    std::vector<std::vector<Tile*>> graph ( x_length,
        std::vector<Tile*> (y_length));

    // initialize every tile through first pass
    for ( int y = 0 ; y < y_length + 1 ; y++) {
        for ( int x = 0 ; x < x_length + 1 ; x++ ){
            graph[y][x] = &Tile2d(x, y);
        }
    }


    // initialize neighbours 
}

Map::Map(int x_length, int y_length, int z_length) {
    // set max dimensions vector 
    max_dimensions = { x_length, y_length, z_length };

    // !!! IMPORTANT NOTE : when creating smaller tiles, we will need to do a 
    // search from the closest tile :
    /* 
    1. select closest node 
    2. recursively search ( x/y/z should be like a binary tree)
    (next closest in x to tile x=3 has x=3.5, then x=3.75 )
    */
    std::vector<std::vector<std::vector<Tile3d*>>> graph(z_length,
        std::vector<std::vector<Tile3d*>>(y_length,
            std::vector<Tile3d*>(x_length)));
    
    
    // initialize every tile through first pass
    for (int z = 0; z < max_dimensions[2] ; z++ ){
        for ( int y = 0 ; y < max_dimensions[1] ; y ++ ) {
            for ( int x = 0 ; x < max_dimensions[0] ; x++ ) {
                graph[x][y][z] = &Tile3d(x, y, z);
            }
        }
    }
    
    // assign neighbours
    for (int x = 0; x < max_dimensions[0] ; x++ ){
        for ( int y = 0 ; y < max_dimensions[1] ; y ++ ) {
            for ( int z = 0 ; z < max_dimensions[2] ; z++ ) {
                graph[x][x][z]->assignNeighbours(get_neighours(x, y, z));
            }
        }
    }
}



std::vector<Tile3d*> Map::get_neighours(int x, int y, int z){
    Tile3d* tile = graph[x][y][z];
    std::vector<Tile> neighbours;
    for (int i = -1 ; i < 2 ; i++) {
        // trigonometry circle
        for (int j = 0 ; j < 8 ; j++){
            if ( i != 0) { neighbours.push_back(this->graph[x+i][y][z]);}
        }
    }
}


std::vector<Tile2d*> Map::get_neighours(int x, int y){
    Tile* tile = &graph[x][y];
    std::vector<Tile> neighbours;
    // trigonometry circle
    for (int i = 0 ; i < 8 ; i++){
        if ( i != 0) { neighbours.push_back(this->graph[x+i][y]);}
    }
}