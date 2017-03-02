//Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/application/Application.hpp>


namespace ncursespp { namespace application {

	Application::Application() : run(true)
	{
        GlobalLogger::log(TRACE) << "Initialising C++ ncurses application" << Sentinel::END;

        initscr();                      /* Start curses mode              */
        cbreak();
        noecho();
        keypad(appWindow.getHandle(), TRUE);
        appWindow.move(coord2d(3,1));
        appWindow.print("Hello");

        C_GUI = new GUI();
        applicationCommands.Add(std::bind( &Application::End, this), 10);
	}

	Application::~Application()
	{
        GlobalLogger::log(TRACE) << "Calling application destructor, cleaning up resources" << Sentinel::END;
        delete C_GUI;
        C_GUI = nullptr;

        endwin();                       /* End curses mode                */
        GlobalLogger::log(TRACE) << "Successfully cleaned up, exiting main\n" << Sentinel::END;
	}

    void Application::Run()
    {
        while (run)
        {
            C_GUI->Render();
            int input = getch();
            applicationCommands.parseInput(input);
            C_GUI->Update();
        }
    }

    void Application::addWindow(string ID, Window* win)
    {
        C_GUI->addWindow(ID, win);
    }

}}
