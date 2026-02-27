/***************************************************************
 * Tile data structure (with methods?)
 **************************************************************/

#include <stdint.h>
#include "Seed.h"

namespace grammar
{

    struct Tile
    {
        uint16_t TypeId = 0;
        uint8_t flags = 0;
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint16_t _reserved;

        Seed seed;
    };


}