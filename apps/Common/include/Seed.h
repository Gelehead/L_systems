/***************************************************************
 * Starting point of the app, will initialize fronted and 
 * backend ports and will have the while true loop
 *
 **************************************************************/

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
        Seed rootSeed;
        
        // each map has a SeedSystem that it can use to find chunk seeds
        void initialize(Seed root) { rootSeed = root; }

        // you can find a chunk seed based on chunk coordinates 
        
    };
}