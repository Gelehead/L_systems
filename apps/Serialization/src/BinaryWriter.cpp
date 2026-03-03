#include "BinaryWriter.h"
#include "Tile.h"

namespace grammar
{
    void BinaryWriter::writeU8(uint8_t v) {buffer.push_back(v);}
    void BinaryWriter::writeU16(uint16_t v) 
    {
        for (int i = 0; i < 2; ++i)
        {
            buffer.push_back((v >> (i * 8)) & 0xFF);
        }
    }
    void BinaryWriter::writeU32(uint32_t v) 
    {
        for (int i = 0; i < 4; ++i)
        {
            buffer.push_back((v >> (i * 8)) & 0xFF);
        }
    }
    void BinaryWriter::writeU64(uint64_t v) 
    {
        for (int i = 0; i < 8; ++i)
        {
            buffer.push_back((v >> (i * 8)) & 0xFF);
        }
    }
    // ! not final
    // 4 + 1 + 4 + 4 + 4 + 8 = 25 bytes total
    void BinaryWriter::writeTile(const Tile& tile)
    {
        writeU32(tile.TypeID | (static_cast<uint32_t>(tile._reserved) << 16));
        writeU8(tile.flags);
        writeU32(tile.x);
        writeU32(tile.y);
        writeU32(tile.z);
        writeU64(tile.seed);
    }

    void BinaryWriter::clear() { buffer.clear(); }
}