#pragma once
#include <ucurses/window/Window.hpp>

namespace ucurses {

	class Interface
	{
		public:

			void Bind(Window* win);

		protected:

			virtual void Initialize() = 0;

			coord2d pos;
			Window* target;
	};

}
