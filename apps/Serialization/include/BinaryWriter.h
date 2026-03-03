/***************************************************************
 * Takes existing structures to pass into uint8 buffers 
 * 
 **************************************************************/

#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <vector>
#include <cstdint>
#include "Tile.h"

namespace grammar
{
    class BinaryWriter
    {
    public:
        void writeTile(const Tile& tile);
        void clear();
        const std::vector<uint8_t>& getbuffer() const { return buffer; }
    private:
        std::vector<uint8_t> buffer;

        void writeU8 (uint8_t  v);
        void writeU16(uint16_t v);
        void writeU32(uint32_t v);
        void writeU64(uint64_t v);
    };
}

#endif // BINARYWRITER_H