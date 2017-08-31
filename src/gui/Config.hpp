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
			static void Escape(Window* win, SliderMenu* menu);

			static void Save(SliderMenu* menu);
			static bool LoadSliders(SliderMenu* menu);
			static void Load();
		
			static std::string config;
	};

}
