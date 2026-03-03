#include "BinaryReader.h"
#include "Tile.h"

namespace grammar
{
    void BinaryReader::init(const std::vector<uint8_t>& buffer)
    {
        data = buffer.data();
        size = buffer.size();
        pos = 0;
    }

    uint8_t BinaryReader::readU8()
    {
        uint8_t v = 0;
        for (int i = 0; i < 1; ++i)
        {
            v |= static_cast<uint8_t>(data[pos++]);
        }
        return v;
    }

    uint16_t BinaryReader::readU16()
    {
        uint16_t v = 0;
        for (int i = 0; i < 2; ++i)
        {
            v |= static_cast<uint16_t>(data[pos++]);
        }
        return v;
    }
    
    uint32_t BinaryReader::readU32()
    {
        uint32_t v = 0;
        for (int i = 0; i < 4; ++i)
        {
            v |= static_cast<uint32_t>(data[pos++]);
        }
        return v;
    }

    uint64_t BinaryReader::readU64()
    {
        uint64_t v = 0;
        for (int i = 0; i < 8; ++i)
        {
            v |= static_cast<uint64_t>(data[pos++]);
        }
        return v;
    }

    // 25 bytes total
    Tile BinaryReader::readTile()
    {
        Tile tile;
        uint32_t word0  = readU32();
        tile.TypeID     = word0 & 0xFFFF;
        tile._reserved  = static_cast<uint16_t>(word0 >> 16);
        tile.flags      = readU8(); 
        tile.x          = readU32();
        tile.y          = readU32();
        tile.z          = readU32();
        tile.seed       = readU64();

        return tile;
    }
}