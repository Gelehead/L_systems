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
        uint8_t x;
        uint8_t y;
        uint8_t z;
        
    };
}