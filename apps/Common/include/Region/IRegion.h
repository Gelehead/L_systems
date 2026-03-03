/***************************************************************
* Interface file for region types files 
* should be implemented by Domain, region, area, site
****************************************************************/

#ifndef IREGION_H
#define IREGION_H

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
    public:
        virtual void IRegion() = 0;
        // virtual ~IRegion() = default;

        /***************************************************************
        * Defined in children class at definition
        **************************************************************/
        virtual RegionLevel level() const = 0;
        virtual float influence()   const = 0;
        virtual uint32_t id()       const = 0;
        virtual Seed seed()         const = 0;

        /***************************************************************
        * Tells by deterministic algorithm, using seed, if coordinates 
        * are inside the region
        **************************************************************/
        virtual bool contains(std::vector<uint32_t> coordinates, Seed seed) = 0;
    };
}

#endif // IREGION_H