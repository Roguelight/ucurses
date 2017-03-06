// Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

/*
 * C++ wrapper around ncurses
 */

#pragma once
#include <ctk/log/GlobalLogger.hpp>

#include <ncurses.h>

#include <ncursespp/application/GUI.hpp>
#include <ncursespp/gui/Command.hpp>
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
            void End(); 
            void addWindow(string ID, Window* win);  
            
        protected:

            GUI* C_GUI;
            /* 
             * The prefix C_ indicates the variable points to an important component that 
             * is a part of this class. This distinguishes pointers to shared objects
             * from pointers to components that should be constructed once.
             */ 

            CommandArray Commands;

            bool running;
            void addCommand(delegate function, int key);
            /*
             * Called in children class to customise application functionality
             */

        private:

            void Parse();

	};

}};
