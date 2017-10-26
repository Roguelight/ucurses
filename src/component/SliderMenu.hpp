// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * Supports multiple sliders in a menu
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/menu_template.hpp>
#include <ucurses/component/Slider.hpp>
#include <vector>

namespace ucurses { 

#define NOSELECT -1

	class SliderMenu : public Component, public menu_template<basic_slider>
	{
		using index = short;

		public:

			SliderMenu(Window* host, coord x = 0, coord y = 0);


			void showHelp();

		protected:

			virtual void Draw();
			void incrementActive();
			void decrementActive();
			
			virtual void bindDefault();
			virtual void Process(int input);

	};

}
