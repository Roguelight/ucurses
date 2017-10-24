/*
 *
 *
 */

#pragma once
#include <ucurses/window/Window.hpp>

namespace ucurses {

	class Interface
	{
		public:

			Interface() = default;

			virtual void Bind(Window* win);
			void setPosition(coord x, coord y);


		protected:

			Window* win;
			coord2d pos = coord2d(2,2);
	};

}

/*
 * class MainMenu : public Interface
 * {
 *
 * };
 *
 * window->bindInterface(new MainMenu());
 * or
 * mainMenu->Bind(window);
 *
 */
