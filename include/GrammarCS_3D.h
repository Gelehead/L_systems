#ifndef GRAMMAR_CS_3D_H
#define GRAMMAR_CS_3D_H

#include "GrammarUnified.h"
#include "Tile.h"

class GrammarCS_3D : public GrammarUnified {
public: 
    GrammarCS_3D(
        const std::vector<Tile*> non_terminal,
        const std::vector<Tile*> terminal,
        const std::vector<Tile*> start

    );

};

#endif
