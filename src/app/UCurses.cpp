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
        curs_set(0);
		keypad(stdscr, TRUE);

		// Tab next
		Commands.Add('d', std::bind( &WindowContainer::Previous, &Windows));  
		Commands.Add('f', std::bind( &WindowContainer::Next, &Windows));  
		tips.push_back("Tab: Switch window");

		// End Application
		Commands.Add(KEY_F(4), std::bind( &UCurses::End, this));
		tips.push_back("F1: Quit");

		// Delete active window
		Commands.Add(KEY_F(2), std::bind( &WindowContainer::RemoveActive, &Windows));

		// Allow windows to create more windows
		Window::ucurses = this;
	}

	void UCurses::Start()
	{
		Render();
		running = true;
	}

	void UCurses::Run()
	{
		Start();
		while( Running() )
		{
        	handleInput();
			Render();
		}	
	}

	UCurses::~UCurses()
	{
		endwin();	// End curses mode
	}

	void UCurses::handleInput()
	{
		int input = Windows.getInput();
		Commands.Process(input);
		Windows.Process(input);
	}

	void UCurses::Render()
	{
		/* Seperating refreshing individual windows from updating the virtual 
		 * screen increases efficiency by minimising the redundant calls to hidden
		 * doupdate() function which is called by wrefresh() */
		Windows.ClearAll();
		Windows.Refresh(); // Copies windows to virtual window
		doupdate();        // Compares virtual to physical and updates screen
	}

	void UCurses::End()
	{
		running = false;
	}

	bool UCurses::Running() const
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

    void UCurses::loadConfig(const std::string& filepath)
	{
		ifstream file(filepath, ios_base::in);
		if (file.good())
		{
			float values[3]; 

			for (int i = 0; i < 3; ++i)
				file >> values[i];

			init_pair(1, values[0], values[1]);
			init_pair(2, values[2], values[1]);
		}
	}
}
