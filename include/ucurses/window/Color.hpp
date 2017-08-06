/*
 * Lightweight interface for accessing ncurses colors. Provides safety in 
 * initializing color pairs and defining new colors
 *
 * NCurses defines the following colors.
 *
 *		COLOR_...
 *		BLACK
 *		RED
 *		GREEN
 *		YELLOW
 *		BLUE
 *		MAGENTA
 *		CYAN
 *		WHITE
 *
 *  Essentially wraps the listed NCurses functions and provides a safe way of
 *  accessing and initializing new color pairs
 *
 *	init_pair(short pair, short f, short b)
 *	init_color(short color, short r, short g, short b);
 *
 */

#pragma once
#define INVALIDCOLOR -1
#include <ncurses.h>


namespace ucurses { 

    using namespace std;
            
    class ColorContainer
    {
            
        public: 

            ColorContainer();

			// Returns value of new pair
            short Add(short foreground, short background);
			// Returns value of new color
			short Define(short r, short g, short b);

			short isValid(short color_pair); // Returns zero if not

        private:

			short size; // 0
			short colors; // 50
    };
    
}
