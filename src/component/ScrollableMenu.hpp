/*
 * Supports automatic scrolling with selection change
 * Suitable for menus with many items
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/Menu.hpp>

namespace ucurses { 
			
	class ScrollableMenu : public Menu
	{
		public:
	
			ScrollableMenu(Window* host, coord x = 0, coord y = 0);

            void setRange(short s);

		protected:

			virtual void Draw();

			int range = 5;
			/* 
			 * short selection; (inherited)
			 * calculate item range from numShown and selection
			 */

	};
}
