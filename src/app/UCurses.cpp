#include <ucurses/window/WindowContainer.hpp>
#include <ucurses/window/Window.hpp>
#include <ucurses/app/UCurses.hpp>

namespace ucurses { 

	UCurses::UCurses() : running(true), help(false)
	{
		initscr();                      /* Start curses mode    */
		Colors.Initialize();
		Window::colors = &Colors;
		noecho();
		cbreak();
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

	void UCurses::Start()
	{
		Clear();
		Render();
		running = true;
	}

	void UCurses::Run()
	{
		Start();
		while( Okay() )
		{
			int key = getInput();
        	handleInput(key);
			Clear();
			Render();
		}	
	}

	UCurses::~UCurses()
	{
		endwin();	// End curses mode
	}

	void UCurses::Clear()
	{
		Windows.ClearAll();
	}

	void UCurses::handleInput(int input)
	{
		Commands.Process(input);
		Windows.Process(input);
	}

	int UCurses::getInput()
	{
		return Windows.getInput();
	}

	void UCurses::Render()
	{
		/* Seperating refreshing individual windows from updating the virtual 
		 * screen increases efficiency by minimising the redundant calls to hidden
		 * doupdate() function which is called by wrefresh() */
		Windows.Refresh(); // Copies windows to virtual window
		doupdate();        // Compares virtual to physical and updates screen
	}

	void UCurses::End()
	{
		running = false;
	}

	bool UCurses::Okay() const
	{
		return running;
	}          

	Window* UCurses::getActiveWindow()
	{
		return &(Windows.getActive()); 
	}

	coord2d UCurses::getSize() const
	{ 
		return Windows[0].getSize(); 
	}

	Window* UCurses::createWindow(coord2d size, coord2d pos)
	{
		return Windows.Create(size, pos);          
	}

	Window* UCurses::createWindow()
	{
		return Windows.Create();          
	}

	void UCurses::removeAll()
	{
		Windows.RemoveAll(); 
	}

	void UCurses::addCommand(int key, delegate function)
	{
		Commands.Add(key, function);
	}

	void UCurses::setHelp(bool b)
	{ 
		help = b; 
	}

	bool UCurses::showHelp()
	{ 
		return help; 
	}

	const std::vector<string>& UCurses::getTips() const
	{
		return tips;
	}

}
