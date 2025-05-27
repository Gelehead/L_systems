#include "noise.h"
#include "Map.h"

#define LENGTH 200

int main(int argc, char** argv) {
    /* purpose of this main : 
        1. Create a 2d graph as a proof of concept for the map
            1.1 find a way to display the tiles2d lmao
            1.2 uhh
        2. 3d graph rahhh
    *
    * 
    */

    noise noiseGen(1, LENGTH);
    noiseGen.perlin(12);

    Map* map = Map::read_json("abc");

    return 0;
}