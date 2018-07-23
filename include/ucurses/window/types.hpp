
#pragma once
#include <ctk/math/Vec2.hpp>

namespace ucurses {

    using coord = short;
    using coord2d = ctk::Vec2<coord>;

    struct Cell
    {
        unsigned char symbol = '.';
        unsigned short color = 6;
        void write_form(std::ostream& stream) const
        { 
            stream << symbol << ' ' << color << std::endl; 
        } 
    };
}
