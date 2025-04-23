#ifndef TILE_H
#define TILE_H

#include <vector>
#include "grammar.h"
#include "noise.h"

enum TileType {
    SAND,
    DEEP_OCEAN,
    WARM_OCEAN,
    COAST,
    FOREST,
    MOUNTAIN
};

class Tile {
protected:
    std::vector<double> position;
    std::vector<double> direction;

public:
    Tile(std::vector<double> pos, std::vector<double> dir);
    Tile();
    virtual ~Tile() = default;

    virtual GrammarElement* propagate() const = 0;
};

class Tile2d : public Tile {
public:
    double x, y;
    Tile2d* parent;
    Tile2d* child;

    // default initialization 
    Tile2d(double x);
    Tile2d();

    GrammarElement* propagate() const override;

    Tile2d* init(int length, int featureSize);
};

#endif
