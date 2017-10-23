#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/menu_template.hpp>

namespace ucurses { 
			
	class ScrollableMenu : public menu_template<std::string>
	{
		public:
	
			ScrollableMenu(coord x, coord y, Window* host);

		protected:

			virtual void Draw();

			unsigned int numShown = 10;

			/* 
			 * short selection; (inherited)
			 * calculate item range from numShown and selection
			 */

	};
	
}
