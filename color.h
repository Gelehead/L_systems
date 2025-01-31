#ifndef COLOR
#define COLOR

#include <vector>

class color{

    public :    
        unsigned char r;
        unsigned char g;
        unsigned char b;

        color(
            unsigned char r,
            unsigned char g,
            unsigned char b
        ) : r(r), g(g), b(b)
        {}

};

#endif