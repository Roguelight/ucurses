
#pragma once
#include <ctk/math/Vec2.hpp>

namespace ucurses {

    using coord = short;
    using coord2d = ctk::Vec2<coord>;

    struct Cell
    {
        Cell(int symbol, short color) : symbol(symbol), color(color) {}

        int symbol = ' ';
        unsigned short color = 1;
        void write_form(std::ostream& stream) const
        { 
            stream << symbol << ' ' << color << std::endl; 
        } 
    };
}
