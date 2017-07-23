// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

/*
 * Handles window storage and color manipulation.
 * Parses input and delegates to the active window.
 *      Input should be passed on like a chain of command
 */

#pragma once
#include <string>

#include <ucurses/window/Color.hpp>
#include <ucurses/window/WindowContainer.hpp>
#include <ucurses/window/types.hpp>

namespace ucurses { 

	class UCurses
	{
		public:

            using Ptr = UCurses*;

			UCurses();
			~UCurses();
            
            void Run();
            
            Window* createWindow(coord2d size, coord2d pos, bool deletable = false);
            Window* createWindow(bool deletable = false);
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
            void Render();
            void End(); 

            bool running;
	};
}
