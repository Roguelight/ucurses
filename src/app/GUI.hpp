// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

/*
 * Handles window storage and color manipulation.
 * Parses input and delegates to the active window.
 *      Input should be passed on like a chain of command
 *      app->GUI->ActiveWindow
 *
 */

#pragma once
#include <string>

#include <ucurses/gui/Color.hpp>
#include <ucurses/gui/WindowContainer.hpp>
#include <ucurses/gui/types.hpp>

namespace ucurses { 

	class GUI
	{
		public:

            using Ptr = GUI*;

			GUI();
			virtual ~GUI();
            
            void Run();
            
            Window* createWindow(coord2d size, coord2d pos);
            Window* createWindow();
            /*
             * Returns a window of maximum size
             */
            
            Window* getActiveWindow();

            void addCommand(int key, delegate function);
            /*
             * UCurses responds to two command arrays.
             * One for application commands (Close, Window tabbing etc)
             * and one for the active window
             */
            
            coord2d getSize() const;                          

        protected:

            void removeAll();

            CommandArray Commands; // GUI level commands. Default is TAB to cycle active window

        private:

            WindowContainer Windows;

            void Parse();
            void Parse(int key);
            void Render();

            void End(); 
            bool running;

            /* Initialization */

            void initCommands();
	};
}
