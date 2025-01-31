#ifndef TURTLE
#define TURTLE

#include <vector>
#include <map>
#include "color.h"

//simplified version of a turtle library
// inspiration see : https://github.com/codemanyak/Turtleizer_CPP
class turtle{
    public : 
        turtle() : x(0), y(0), col(color(255,255,255), pencil_width(10)) {}

        turtle(int x, int y, color color) : x(x), y(y), col(color){}

        void forward(int distance){

        }
        void backward(int distance){ forward(-distance); }

        void right(double angle){

        }
        void left(double angle){ right(-angle); }


    
    private :
        int x, y;
        color col;
        std::map<std::pair<int, int>, color> map;
        int pencil_width;
};

#endif