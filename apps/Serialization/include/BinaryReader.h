/***************************************************************
 * reads binary buffer and transforms to Tile
 **************************************************************/

#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <cstring>
#include <vector>
#include <cstdint>
#include "Tile.h"

namespace grammar 
{

    class BinaryReader
    {
        const uint8_t*  data = nullptr;
        size_t          size = 0;
        size_t          pos  = 0;

        void init(const std::vector<uint8_t>& buffer);
        uint8_t readU8();
        uint16_t readU16();        
        uint32_t readU32();
        uint64_t readU64();
        Tile readTile();

    public: 
        
    };
}