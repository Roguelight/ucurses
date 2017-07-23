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
			
			static void Display(Window* win, std::function<void()> const& exit);
			static void showTips(Window* win);
			static void showTitle(Window* win);
			static void Tab(Window* win);
			static void Extra(Window* win);

	};

}
