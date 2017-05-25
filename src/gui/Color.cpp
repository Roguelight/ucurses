// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/Color.hpp>
#include <ctk/log/GlobalLogger.hpp>

using namespace ctk::log;

namespace ucurses { 

    ColorContainer::ColorContainer()
    {
        GlobalLogger::log(TRACE) << "Initialising ncurses color settings and loading default colors" << Sentinel::END;
        start_color();
        init_color(COLOR_RED, 255, 160, 20); // Change value of COLOR_RED defined in ncurses.h
        colors.reserve(size);

        Add(ColorPair::DEFAULT, COLOR_BLACK, COLOR_RED); 
        Add(ColorPair::INVERSE, COLOR_RED, COLOR_BLACK); 
        Add(ColorPair::BW, COLOR_BLACK, COLOR_WHITE); 
        Add(ColorPair::BLUE, COLOR_BLACK, COLOR_BLUE); 
    }

    void ColorContainer::Add(ColorPair ID, NCURSES_COLOR_T foreground, NCURSES_COLOR_T background)
    {
        //GlobalLogger::log(TRACE) << "Initialising color pair: ID = " << ID << " Count = " << indices.size() + 1 << Sentinel::END;
        init_pair(colors.size(), foreground, background);
        colors.push_back(ID);
    }

    const color ColorContainer::Get(ColorPair ID) const 
    {
        auto pair = std::find(colors.begin(), colors.end(), ID);
        if (pair != colors.end())
        {
            int pairindex = pair - colors.begin();
            GlobalLogger::log(TRACE, "Color") << "Found color" << pairindex << Sentinel::END;
            return COLOR_PAIR(pairindex);
        }
        else 
            GlobalLogger::log(TRACE, "Color") << "Couldn't find color pair with ID: " << Sentinel::END;
    }

}
