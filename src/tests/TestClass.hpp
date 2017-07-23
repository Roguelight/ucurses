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

            ucurses::UCurses gui;
	};

    void mainScreen(Window* target);

}
