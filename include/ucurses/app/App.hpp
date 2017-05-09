// Copyright Fri Feb 17 22:34:14 2017
// Liam Rogers, All rights reserved.

/*
 * C++ wrapper around ncurses
 */

#pragma once
#include <ctk/log/GlobalLogger.hpp>

#include <ncurses.h>

#include <ucurses/app/GUI.hpp>
#include <ucurses/gui/Command.hpp>
#include <ucurses/gui/Window.hpp>

using namespace ctk::log;
using namespace std;

namespace ucurses { namespace app {

	class App
	{
		public:

			App(GUI* Component = new GUI());
			virtual ~App();

            void Run();
            void End(); 
            void addWindow(string ID, Window* win);  
            
        protected:

            GUI* C_GUI;
            /* 
             * The prefix C_ indicates the variable points to an important component that 
             * is a part of this class. This distinguishes pointers to shared objects
             * from pointers to components that should be constructed and destroyed by owner.
             */ 

            CommandArray Commands;

            void addCommand(int key, delegate function); // F1->End(); Ends program

        private:

            void Parse();
            bool running;

	};

}}
