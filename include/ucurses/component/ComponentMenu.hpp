/*
 * Supports automatic scrolling with selection change
 * Suitable for menus with many items
 

#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/Menu.hpp>

namespace ucurses {

	class ComponentMenu : public Component, public menu_template<Component*>
	{

		public:

			ComponentMenu(Window* target, coord x = 0, coord y = 0);

		protected:

			virtual void Draw();
			virtual void Process(int input);

	};

}

*/
