// Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

/*
 * C++ wrapper around ncurses
 */

#pragma once
#include <ctk/log/GlobalLogger.hpp>

#include <ncurses.h>

#include <ncursespp/application/GUI.hpp>
#include <ncursespp/gui/CommandArray.hpp>
#include <ncursespp/gui/Window.hpp>

using namespace ctk::log;
using namespace std;

namespace ncursespp { namespace application {

	class Application
	{
		public:

			Application();
			virtual ~Application();

            void Run();
            void addWindow(string ID, Window* win);  

            void End()                              { run = false; }
            
        protected:

            GUI* C_GUI;
            /* 
             * Important components should have a capital letter
             * and prefix C_ so that the class name can be used as
             * the name. This distinguishes pointers to shared objects
             * from pointers to components that should be constructed once.
             */ 

            CommandArray applicationCommands;
            /*
             * First attempt at data oriented design, check types.h
             * for implementation
             */

            Window appWindow;

            bool run;

	};

}};
