#include <cstdint>

namespace grammar
{
    typedef uint8_t Terrain;
    enum Terrain_ : uint8_t
    {
        Terrain_Sand,
        Terrain_Grass,
        Terrain_Concrete,
        Terrain_WarmOcean,
        Terrain_IcyMountains
    };

} // namespace grammar
