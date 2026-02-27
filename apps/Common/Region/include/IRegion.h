/***************************************************************
* Interface file for region types files 
* should be implemented by Domain, region, area, site
****************************************************************/

#include "Seed.h"
#include <stdint.h>
#include <vector>

namespace grammar 
{
    enum class RegionLevel : uint8_t
    {
        // Biggest
        Domain = 0,
        Region = 1, 
        Area = 2,   // not yet implemented
        Site = 3    // not yet implemented 
        // smallest 
    };

    /***************************************************************
    * Intended to be loaded and unloaded as world is generated
    * always same generation for the same seed
    **************************************************************/
    class IRregion
    {
        virtual void IRegion() = 0;
        virtual ~IRegion() = default;

        virtual Seed seed() = 0;
        
        /***************************************************************
        * Defined in children class at definition
        **************************************************************/
        virtual RegionLevel level() = 0;
        virtual float influence() = 0;

        /***************************************************************
        * Tells by deterministic algorithm, using seed, if coordinates 
        * are inside the region
        **************************************************************/
        virtual bool contains(std::vector<uint32_t> coordinates, Seed seed) = 0;
    };
}

