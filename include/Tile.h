#ifndef TILE_H
#define TILE_H

#define INT_MAX 2100100100

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

// Virtual parent class Tile for every subclass in set dimensions
class Tile {
    public:
        virtual ~Tile() = default;

        // propagate / pulse is the signal propagated amongst all nodes a signal(query*)
        // *see Query file in documentation
        virtual Consistuent* propagate() const;
        virtual std::vector<Consistuent> Query() const;
        virtual void assignNeighbours(std::vector<Tile*> neighbours)const;

    private : 
        Tile* parent;
        std::vector<Tile> children;
        std::vector<Tile> neighbours;
        int entropy = INT_MAX;
};

class Tile2d : public Tile {
public:
    double x, y;

    Consistuent* propagate() const override;
    std::vector<Consistuent> Query() const override;
    void assignNeighbours(std::vector<Tile*> neighbours)const override;


    // default initialization 
    Tile2d(double x, double y);
    Tile2d();
};

class Tile3d : public Tile {
    public :
        // should be useful to have double instead of int for subdivision
        double x, y, z;

        Consistuent* propagate() const override;
        std::vector<Consistuent> Query() const override;
        void assignNeighbours(std::vector<Tile*> neighbours)const override;
    

        // initialization
        Tile3d(double x, double y, double z );
        Tile3d();
};

// should it contain the rules applied to it for the next generation?
class Cell : public Tile3d {
    public :
        double max_lifespan;
        double remaining_lifespan;
};

#endif
