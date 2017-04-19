// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

/*
 * Handles window storage and color manipulation.
 * Parses input and delegates to the active window.
 *      Input should be passed on like a chain of command
 *      Application->GUI->ActiveWindow
 *
 */

#pragma once
#include <string>

#include <ctk/log/GlobalLogger.hpp>
#include <ncursespp/gui/WindowContainer.hpp>
#include <ncursespp/gui/Color.hpp>
#include <ncursespp/application/types.hpp>

using namespace ctk::log;
using namespace ncursespp::gui;

namespace ncursespp { namespace application {

	class GUI
	{
        friend class Application;

		public:

			GUI();
			virtual ~GUI();
            
            coord2d getSize() const;                          

        protected:

            void addWindow(string ID, Window* win);
            void removeAll();
            Window& getActiveWindow();

            CommandArray Commands; // GUI level commands. Default is TAB to cycle active window
            Window stdscreen;      // Handle to the curses stdscr through a nice C++ class
            
            virtual void Load() {}

        private:

            WindowContainer Windows;

            void Parse(int input);
            void Render();
            void UpdateAll();
            void UpdateActive();
            
	};

}}


