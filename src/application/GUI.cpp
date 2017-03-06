// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace application {

	GUI::GUI()
	{
        GlobalLogger::log(TRACE) << "Initialising ncursespp GUI" << Sentinel::END;

        Commands.Add(std::bind( &WindowContainer::Next, &Windows), 9); 
        Windows.Add("Standard Screen", new Window());

        keypad(stdscr, TRUE);
	}

	GUI::~GUI()
	{
        GlobalLogger::log(TRACE) << "Destroying ncursespp GUI" << Sentinel::END;
	}

    void GUI::Render()
    {
        /* Seperating refreshing individual windows from updating the virtual 
         * screen increases efficiency by minimising the redundant calls to hidden
         * doupdate() function which is called by wrefresh() */

        Windows.Refresh(); // Copies windows to virtual window
        doupdate();        // Compares virtual to physical and updates screen
    }

    void GUI::Update()
    {
        Windows.Update(); // Virtual function called on each window to update display
    }

    void GUI::Parse(int input)
    {
        if (!(Commands.Parse(input)))
            Windows.Parse(input);
    }

}}
