// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/Color.hpp>
#include <ctk/log/GlobalLogger.hpp>

using namespace ctk::log;

namespace ucurses { 

    ColorContainer::ColorContainer() : size(0), colors(50)
    {
    }

    short ColorContainer::Add(short foreground, short background)
    {
        init_pair(size, foreground, background);
		short temp = size++;
		return temp;
    }
    short ColorContainer::Define(short r, short g, short b)
	{
		init_color(colors, r, g, b);
		return colors++;
	}

	short ColorContainer::isValid(short color)
	{
		if(color > size)
			return 0;
		else
			return color;
	}
}
