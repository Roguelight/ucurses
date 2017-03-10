// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Window.hpp>

namespace ncursespp { namespace gui {

	class TextEntry : public Window
	{
		public:

			TextEntry(coord x, coord y, string subject); //Default size is small

        protected:

            void Update();


            string subject;
            string input;
            coord2d pos;

            // Commands
            void getInput(); // *->E
            void printCommands();

	};

}}
