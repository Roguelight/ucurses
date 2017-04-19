// Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/application/Application.hpp>


namespace ncursespp { namespace application {

	Application::Application(GUI* Component) : running(true), C_GUI(Component)
	{
        GlobalLogger::log(TRACE,"NCursespp:CTOR:") << "Initialising C++ ncurses application" << Sentinel::END;

        initscr();                      /* Start curses mode    */
        noecho();
        raw();
        curs_set(0);                    /* Invisible cursor (if program crashes, cursor remains invisible) */
        keypad(stdscr, TRUE);
        C_GUI->Load();

        addCommand(KEY_F(1), std::bind( &Application::End, this));
	}

	Application::~Application()
	{
        GlobalLogger::log(TRACE,"NCursespp:DTOR:") << "Calling application destructor, cleaning up resources" << Sentinel::END;
        delete C_GUI;
        C_GUI = nullptr;

        endwin();                       /* End curses mode                */
        GlobalLogger::log(TRACE,"NCursespp:DTOR:") << "Successfully cleaned up, exiting main\n" << Sentinel::END;
	}

    void Application::Run()
    {
        GlobalLogger::log(TRACE,"NCursespp:") << "Starting application loop" << Sentinel::END;
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
        GlobalLogger::log(TRACE,"NCursespp:") << "Adding window through application method with ID: " << ID << Sentinel::END;
        C_GUI->addWindow(ID, win);
    }
    
    void Application::addCommand(int key, delegate function)
    {
        GlobalLogger::log(TRACE,"NCursespp:") << "Adding application command" << Sentinel::END;
        Commands.Add(key, function);
    }

    void Application::Parse()
    {
            GlobalLogger::log(TRACE,"App") << "Waiting for input...";
            int input = getch();
            GlobalLogger::log(TRACE,"App") << "Passing key... " << input << Sentinel::END;
            if (!(Commands.Parse(input)))
                C_GUI->Parse(input);
            else
                GlobalLogger::log(TRACE,"App") << "Command caught by application " << input << Sentinel::END;
    }


}}
