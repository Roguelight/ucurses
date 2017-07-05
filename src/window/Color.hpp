// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

/*
 * Lightweight interface for accessing ncurses colors
 */

#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include <ncurses.h>


namespace ucurses { 

    using namespace std;
    using colorindex = uint8_t; // used to identify an initialised pair; 1 byte 
    using color = short; // ncurses uses 16bit integers for COLOR_PAIR
            
    enum class ColorPair : char { DEFAULT, INVERSE, BW, BLUE };

    class ColorContainer
    {
            
        public: 

            ColorContainer();

            const color Get(ColorPair ID) const;
            void Add(ColorPair ID, short foreground, short background);

        private:

            vector<ColorPair> colors;

            const size_t size = 8;
    };
    
}
