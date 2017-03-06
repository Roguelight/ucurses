// Copyright Sat Feb 25 17:23:15 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Color.hpp>


namespace ncursespp { namespace gui {

    ColorContainer::ColorContainer()
    {
        GlobalLogger::log(TRACE) << "Initialising ncurses color settings and loading default colors" << Sentinel::END;
        start_color();
        init_color(COLOR_RED, 255, 160, 20); // Changine value of COLOR_RED defined in ncurses.h
        indices.reserve(size);
        keys.reserve(size);

        Add("Default", COLOR_BLACK, COLOR_RED); 
        Add("Inverse", COLOR_RED, COLOR_BLACK); 
        Add("BW", COLOR_BLACK, COLOR_WHITE); 
        Add("Blue", COLOR_BLACK, COLOR_BLUE); 
    }

    void ColorContainer::Add(string ID, NCURSES_COLOR_T foreground, NCURSES_COLOR_T background)
    {
        GlobalLogger::log(TRACE) << "Initialising color pair: ID = " << ID << " Count = " << indices.size() + 1 << Sentinel::END;
        indices.push_back(indices.size() + 1);
        keys.push_back(ID);
        init_pair(indices.size(), foreground, background);
    }

    const color ColorContainer::Get(string ID) const
    {
        auto key = std::find(keys.begin(), keys.end(), ID);
        if (key != keys.end())
        {
            int keyindex = key - keys.begin();
            return COLOR_PAIR(indices[keyindex]);
        }
        else
            GlobalLogger::log(TRACE, "ColorContainer") << "Couldn't find color pair with ID: " << ID << Sentinel::END;
    }

}}
