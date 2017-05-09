// Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

#include <ucurses/app/App.hpp>


namespace ucurses { namespace app {

	App::App(GUI* Component) : running(true), C_GUI(Component)
	{
        GlobalLogger::log(TRACE,"ucurses:CTOR:") << "Initialising C++ ncurses App" << Sentinel::END;

        initscr();                      /* Start curses mode    */
        noecho();
        raw();
        curs_set(0);                    /* Invisible cursor (if program crashes, cursor remains invisible) */
        keypad(stdscr, TRUE);
        C_GUI->Load();

        addCommand(KEY_F(1), std::bind( &App::End, this));
	}

	App::~App()
	{
        GlobalLogger::log(TRACE,"ucurses:DTOR:") << "Calling app destructor, cleaning up resources" << Sentinel::END;
        delete C_GUI;
        C_GUI = nullptr;

        endwin();                       /* End curses mode                */
        GlobalLogger::log(TRACE,"ucurses:DTOR:") << "Successfully cleaned up, exiting main\n" << Sentinel::END;
	}

    void App::Run()
    {
        GlobalLogger::log(TRACE,"ucurses:") << "Starting app loop" << Sentinel::END;
        while (running)
        {
            C_GUI->UpdateAll(); // Write everything to screens
            C_GUI->Render(); // Render screen
            Parse();         // Parse new commands
        }
    }

    void App::End()
    {
        running = false;
    }

    void App::addWindow(string ID, Window* win)
    {
        GlobalLogger::log(TRACE,"ucurses:") << "Adding window through App method with ID: " << ID << Sentinel::END;
        C_GUI->addWindow(ID, win);
    }
    
    void App::addCommand(int key, delegate function)
    {
        GlobalLogger::log(TRACE,"ucurses:") << "Adding App command" << Sentinel::END;
        Commands.Add(key, function);
    }

    void App::Parse()
    {
            GlobalLogger::log(TRACE,"App") << "Waiting for input...";
            int input = getch();
            GlobalLogger::log(TRACE,"App") << "Passing key... " << input << Sentinel::END;
            if (!(Commands.Parse(input)))
                C_GUI->Parse(input);
            else
                GlobalLogger::log(TRACE,"App") << "Command caught by app " << input << Sentinel::END;
    }


}}
