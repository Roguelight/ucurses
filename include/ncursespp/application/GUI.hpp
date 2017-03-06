// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

/*
 * Handles window storage and color manipulation.
 * Parses input and delegates to the active window.
 *      Input should be passed on like a chain of command
 *
 *      Application.getInput(); // If not an application function key pass to GUI
 *      GUI.parseInput();       // If not a GUI specific (like TAB) pass to active window
 */

#pragma once
#include <string>

#include <ctk/log/GlobalLogger.hpp>
#include <ncursespp/gui/Window.hpp>
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
            void Render();
            void Update();
            void addWindow(string ID, Window* win)     { Windows.Add(ID, win);          }
            Window& getActiveWindow()                  { return *(Windows.getActive()); }

        private:

            WindowContainer Windows;
            
            CommandArray Commands;

            void Parse(int input);
            
	};

}}


