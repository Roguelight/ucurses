/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>
#include <functional>

namespace ucurses { 

	class Intro
	{
		public:
			
			static void Display(Window* win);
			static void showTips(Window* win);
			static void showTitle(Window* win);
			static void Tab(Window* win);
			static void Extra(Window* win);
			static void Component(Window* win);
			static void Select(Window* win, Menu* menu, Label* display);
			static void Finish(Window* win, TextEntry* entry);

	};

}
