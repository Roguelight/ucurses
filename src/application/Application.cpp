//Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/application/Application.hpp>


namespace ncursespp { namespace application {

	Application::Application(GUI* init) : running(true), C_GUI(init)
	{
        GlobalLogger::log(TRACE, "NCursespp:App") << "Initialising C++ ncurses application" << Sentinel::END;

        initscr();                      /* Start curses mode    */
        noecho();
        raw();
        curs_set(0);                    /* Invisible cursor     */
        addCommand(std::bind( &Application::End, this), KEY_F(1));
	}

	Application::~Application()
	{
        GlobalLogger::log(TRACE, "NCursespp:App") << "Calling application destructor, cleaning up resources" << Sentinel::END;
        delete C_GUI;
        C_GUI = nullptr;

        endwin();                       /* End curses mode                */
        GlobalLogger::log(TRACE, "NCursespp:App") << "Successfully cleaned up, exiting main\n" << Sentinel::END;
	}

    void Application::Run()
    {
        GlobalLogger::log(TRACE, "NCursespp:App") << "Starting application loop" << Sentinel::END;
        while (running)
        {
            C_GUI->UpdateAll(); // Write everything to screens
            C_GUI->Render(); // Render screen
            Parse();         // Parse new commands
        }
    }

    void Application::End()
    {
        running = false;
    }

    void Application::addWindow(string ID, Window* win)
    {
        C_GUI->addWindow(ID, win);
    }
    
    void Application::addCommand(delegate function, int key)
    {
        Commands.Add(function, key);
    }

    void Application::Parse()
    {
            GlobalLogger::log(TRACE, "NCursespp:App") << "Waiting for input..." << Sentinel::END;
            int input = getch();
            GlobalLogger::log(TRACE, "NCursespp:App") << "Passing key... " << input << Sentinel::END;
            if (!(Commands.Parse(input)))
                C_GUI->Parse(input);
    }


}}
