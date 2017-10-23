#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/menu_template.hpp>

namespace ucurses { 
			
	class ScrollableMenu : public Menu
	{
		public:
	
			ScrollableMenu(Window* host, coord x = 0, coord y = 0);

		protected:

			virtual void Draw();
			virtual void bindDefault();

			unsigned int numShown = 10;

			/* 
			 * short selection; (inherited)
			 * calculate item range from numShown and selection
			 */

	};
}
