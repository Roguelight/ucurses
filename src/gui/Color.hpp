// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

/*
 * Lightweight interface for accessing ncurses colors
 */

#pragma once
#include <vector>
#include <ncurses.h>
#include <ctk/log/GlobalLogger.hpp>
#include <string>
#include <algorithm>

using namespace ctk::log;
using namespace std;

namespace ncursespp { namespace gui {

    using colorindex = uint8_t; // used to identify an initialised pair; 1 byte 
    using color = short; // ncurses uses 16bit integers for COLOR_PAIR

    class ColorContainer
    {
            
        public: 
            
            ColorContainer();

            const color Get(string ID) const;
            void Add(string ID, NCURSES_COLOR_T foreground, NCURSES_COLOR_T background);

        private:

            vector<colorindex> indices;
            vector<string> keys;
    };
}}
