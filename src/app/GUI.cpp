// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/WindowContainer.hpp>
#include <ucurses/gui/Window.hpp>
#include <ucurses/app/GUI.hpp>

namespace ucurses { namespace app {

	GUI::GUI()
	{
        GlobalLogger::log(TRACE, "GUI:CTOR") << "Initialising ucurses GUI" << Sentinel::END;
        Commands.Add(9, std::bind( &WindowContainer::Next, &Windows)); 
        keypad(stdscr, TRUE);
	}

	GUI::~GUI()
	{
        GlobalLogger::log(TRACE, "GUI:DTOR") << "Destroying ucurses GUI" << Sentinel::END;
	}

    void GUI::Render()
    {
        /* Seperating refreshing individual windows from updating the virtual 
         * screen increases efficiency by minimising the redundant calls to hidden
         * doupdate() function which is called by wrefresh() */

        wnoutrefresh(stdscr);
        Windows.Refresh(); // Copies windows to virtual window
        doupdate();        // Compares virtual to physical and updates screen
    }
            
    void GUI::UpdateAll()
    {
        GlobalLogger::log(TRACE, "GUI:") << "Updating all windows" << Sentinel::END;
        Windows.UpdateAll(); // Virtual function called on each window to update display
    }

    Window& GUI::getActiveWindow()
    {
        return *(Windows.getActive()); 
    }

    coord2d GUI::getSize() const
    { 
        return stdscreen.getSize(); 
    }
            
    void GUI::addWindow(string ID, Window* win)
    {
        Windows.Add(ID, win);          
    }

    void GUI::removeAll()
    {
        Windows.RemoveAll(); 
    }

    void GUI::UpdateActive()
    {
        GlobalLogger::log(TRACE, "GUI:") << "Updating active window" << Sentinel::END;
        Windows.UpdateActive(); 
    }

    void GUI::Parse(int input)
    {
        GlobalLogger::log(TRACE, "GUI:") << "Passing command to gui..." << Sentinel::END;
        if (!(Commands.Parse(input)))
            Windows.Parse(input);
        else
            GlobalLogger::log(TRACE, "ucurses:App") << "Command caught by GUI " << input << Sentinel::END;
    }

}}
