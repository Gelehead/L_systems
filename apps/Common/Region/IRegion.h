/***************************************************************
* Interface file for region types files 
* should be implemented by Domain, region, area, site
****************************************************************/

#include <stdint.h>

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

    class IRregion
    {
        virtual IRegion() = 0;
        virtual ~IRegion() = default;

        virtual getContext() = 0;
    }
}

