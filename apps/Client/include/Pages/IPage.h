#ifndef IPAGE_H
#define IPAGE_H

#include <vector>

namespace grammar
{
    namespace Client
    {
        namespace Pages
        {
            /***************************************************************
            * Interface of a page, every page should implement this class  
            **************************************************************/
            class IPage
            {
                virtual IPage() = 0;
                virtual ~IPage() = default;
                
                /***************************************************************
                * Create empty instance of page in higher level logic then initialize it
                * position is in 3d to account for depth (if need be)  
                **************************************************************/
                virtual void initialize(std::vector<float>[3] position, std::vector<float>[2] size) = 0;

                virtual void draw();
            }
        }
    }
}

#endif // IPAGE_H