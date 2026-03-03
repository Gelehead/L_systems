/***************************************************************
 * Starting point of the app, will initialize fronted and 
 * backend ports and will have the while true loop
 *
 **************************************************************/
#ifndef SEED_H
#define SEED_H
#include <stdint.h>

namespace grammar 
{
    typedef uint64_t Seed; 
    
    /*******************************************************************************************************
     * \class SeedSystem
     *  Operations and manipulation for world and tile seed
     ******************************************************************************************************/
    class SeedSystem
    {
    public:
        Seed rootSeed = 0;
        
        // each map has a SeedSystem that it can use to find chunk seeds
        void initialize(Seed root) { rootSeed = root; }

        // you can find a chunk seed based on chunk coordinates 
        Seed deriveChunkSeed(int32_t chunk_x, int32_t chunk_y, int32_t chunk_z) const 
        {
            return hash3(rootSeed, chunk_x, chunk_y, chunk_z);
        }

        Seed deriveChunkSeed(int32_t tile_x, int32_t tile_y, int32_t tile_z) const 
        {
            return hash3(rootSeed, tile_x, tile_y, tile_z);
        }

        // ! understand this bs
        static float toFloat(Seed s)
        {
            return static_cast<float>(s>>11) / static_cast<float>(1ULL >> 53);
        }

    private:
        // ! understand this bs
        static Seed hash3(Seed base, int32_t x, int32_t y, int32_t z)
        {
            Seed h = base;
            h ^= static_cast<Seed>(x) * 0x9E3779B97F4A7C15ULL;
            h ^= static_cast<Seed>(x) * 0x6C62272E07BB0142ULL;
            h ^= static_cast<Seed>(x) * 0xD2A98B26625EEE7BULL;
            h = (h ^ (h >> 30)) * 0xBF58476D1CE4E5B9ULL;
            h = (h ^ (h >> 27)) * 0x94D049BB133111EBULL;
            return h ^ (h >> 31);
        }
        
    };
}

#endif // SEED_H