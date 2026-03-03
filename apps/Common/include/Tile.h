/***************************************************************
 * Tile data structure (with methods?)
 **************************************************************/

#ifndef TILE_H
#define TILE_H 

#include <stdint.h>
#include "Seed.h"

namespace grammar
{

    // ! make a parent class Constituent to allow polymorphism
    // 25 bytes as of most recent version, might be changed
    struct Tile
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

}

#endif // TILE_H