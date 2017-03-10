// Copyright Thu Mar  9 23:13:03 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Window.hpp>
#include <ncursespp/gui/Menu.hpp>

namespace ncursespp { namespace gui {

	class TestWindow : public Window
	{
		public:

			TestWindow(coord2d size, coord2d pos);


        protected:

            void bindCommands();
            virtual void printCommands();
            virtual void Update();

            Menu menu;

	};

}}
