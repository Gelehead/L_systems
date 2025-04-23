#include "Tile.h"
#include <vector>
#include <random>

// Tile definition

Tile::Tile(
    std::vector<double> pos, 
    std::vector<double> dir
) : position(pos), direction(dir) {}

Tile::Tile() : position(), direction() {}


// Tile2d definition
Tile2d::Tile2d(
    double x
) : x(x), y(), parent(), child() {}
Tile2d::Tile2d() : x(), y(), parent(), child() {}

GrammarElement* Tile2d::propagate() const {
    return nullptr;
}

Tile2d* init(int length) {
    if ( length == 0 ) { return nullptr; }
    
}