/***************************************************************
 * 2D Constituent, used for biome mapping
 **************************************************************/

#ifndef TILE_H
#define TILE_H 

#include <stdint.h>
#include "Seed.h"
#include "Constituent.h"

namespace grammar
{

    struct TilePayload : public ConstituentPayload
    {
        uint16_t TypeID = 0;
        uint8_t flags = 0;
        uint32_t x;
        uint32_t y;
        uint32_t z;
        // will need restructuration if more than 16bits needed
        uint16_t _reserved;

        Seed seed;
    };

    class Tile : public Constituent
    {

    };

}

#endif // TILE_H