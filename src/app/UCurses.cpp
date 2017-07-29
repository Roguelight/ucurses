#include <ucurses/window/WindowContainer.hpp>
#include <ucurses/window/Window.hpp>
#include <ucurses/app/UCurses.hpp>

namespace ucurses { 

	UCurses::UCurses() : running(false)
	{
		help = true;
        initscr();                      /* Start curses mode    */
        noecho();
        raw();
        curs_set(0);                    /* Invisible cursor (if program crashes, cursor remains invisible) */
        keypad(stdscr, TRUE);

		// Tab next
        Commands.Add(9, std::bind( &WindowContainer::Next, &Windows));  
		tips.push_back("Tab: Switch window");

		// End Application
        Commands.Add(KEY_F(1), std::bind( &UCurses::End, this));
		tips.push_back("F1: Quit");

		// Delete active window
        Commands.Add(KEY_F(2), std::bind( &WindowContainer::RemoveActive, &Windows));

		// Allow windows to create more windows
		Window::ucurses = this;
	}

	UCurses::~UCurses()
	{
        endwin();	// End curses mode
	}
    
    void UCurses::Run()
    {
		if (running == false) // Protect against recursive running inside loop
		{
			running = true;

        	while (running)
        	{
            	Windows.UpdateAll(); 
            	Render();       // Render screen
            	Parse();        // Parse new commands
        	}
		}
    } 
    
    void UCurses::End()
    {
        running = false;
    }

    void UCurses::Render()
    {
        /* Seperating refreshing individual windows from updating the virtual 
         * screen increases efficiency by minimising the redundant calls to hidden
         * doupdate() function which is called by wrefresh() */
        Windows.Refresh(); // Copies windows to virtual window
        doupdate();        // Compares virtual to physical and updates screen
    }
            
    Window* UCurses::getActiveWindow()
    {
        return &(Windows.getActive()); 
    }

    coord2d UCurses::getSize() const
    { 
        return Windows[0].getSize(); 
    }
            
    Window* UCurses::createWindow(coord2d size, coord2d pos, bool deletable)
    {
        return Windows.Create(size, pos, deletable);          
    }
    
    Window* UCurses::createWindow(bool deletable)
    {
        return Windows.Create(deletable);          
    }

    void UCurses::removeAll()
    {
        Windows.RemoveAll(); 
    }
    
    void UCurses::addCommand(int key, delegate function)
    {
        GlobalLogger::instance().log(TRACE) << "Adding command to UCurses GUI command vector" << Sentinel::END;
        Commands.Add(key, function);
    }

    void UCurses::Parse()
    {
        int input = Windows.getInput();
        Commands.Parse(input);
        Windows.Parse(input);
    }
}
