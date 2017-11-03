#pragma once
#include <ucurses/ucurses.hpp>

namespace ucurses {

    class Interface
    {
        protected:

            coord2d pos;
            Window* target;
    };
}
