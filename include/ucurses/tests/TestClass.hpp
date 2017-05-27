/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>


namespace ucurses { 

	class TestClass
	{
		public:

			TestClass();

            void Run();

        protected:

            ucurses::GUI gui;
	};

    void mainScreen(Window* target);

}
