// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

#include <fstream>

#include <ucurses/app/Color.hpp>
#include <ucurses/gui/Config.hpp>

#include <ctk/log/GlobalLogger.hpp>

using namespace ctk::log;

namespace ucurses { 

	ColorContainer::ColorContainer() : size(0), colors(0)
	{

	}

	void ColorContainer::Initialize()
	{
		start_color();
		// Default
		init_pair(1, COLOR_WHITE, 3);
		init_pair(2, COLOR_CYAN, 3);
		Config::Load("./color_scheme.conf");
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

	short ColorContainer::Validate(short color)
	{
		if(color > size)
			return 0;
		else
			return color;
	}

    void InitializePair(short primary, short hlid,  short f, short b, short highlight)
    {
		init_pair(primary, f, b);
		init_pair(hlid, b, highlight);
    }
}
