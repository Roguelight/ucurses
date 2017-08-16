/*
 * Color configuration screen for UCurses
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>

namespace ucurses { 

	class Config
	{
		public:

			static void Display(Window* win);
			static void RefreshUI(Window* win, SliderMenu* menu);
		

	};

}
