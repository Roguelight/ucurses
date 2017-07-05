#include <ucurses/window/WindowContainer.hpp>
#include <ucurses/window/Window.hpp>
#include <ucurses/app/GUI.hpp>

namespace ucurses { 

	GUI::GUI() : running(true)
	{
        initscr();                      /* Start curses mode    */
        noecho();
        raw();
        curs_set(0);                    /* Invisible cursor (if program crashes, cursor remains invisible) */
        keypad(stdscr, TRUE);

        Commands.Add(9, std::bind( &WindowContainer::Next, &Windows)); 
        Commands.Add(KEY_F(1), std::bind( &GUI::End, this));
	}

	GUI::~GUI()
	{
        endwin();                       /* End curses mode                */
	}
    
    void GUI::Run()
    {
        while (running)
        {
            Windows.UpdateAll(); 
            Render();       // Render screen
            Parse();        // Parse new commands
        }
    } 
    
    void GUI::End()
    {
        running = false;
    }

    void GUI::Render()
    {
        /* Seperating refreshing individual windows from updating the virtual 
         * screen increases efficiency by minimising the redundant calls to hidden
         * doupdate() function which is called by wrefresh() */
        Windows.Refresh(); // Copies windows to virtual window
        doupdate();        // Compares virtual to physical and updates screen
    }
            
    Window* GUI::getActiveWindow()
    {
        return &(Windows.getActive()); 
    }

    coord2d GUI::getSize() const
    { 
        return Windows[0].getSize(); 
    }
            
    Window* GUI::createWindow(coord2d size, coord2d pos)
    {
        return Windows.Create(size, pos);          
    }
    
    Window* GUI::createWindow()
    {
        return Windows.Create();          
    }

    void GUI::removeAll()
    {
        Windows.RemoveAll(); 
    }
    
    void GUI::addCommand(int key, delegate function)
    {
        GlobalLogger::instance().log(TRACE) << "Adding command to UCurses GUI command vector" << Sentinel::END;
        Commands.Add(key, function);
    }

    void GUI::Parse()
    {
        int input = wgetch(Windows.getActive().getHandle());
        if (!(Commands.Parse(input)))
            Windows.Parse(input);
    }
}
