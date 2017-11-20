#pragma once
#include <ucurses/window/Window.hpp>

namespace ucurses {

	class State
	{
		public:

			void Bind(Window* win);

		protected:

			virtual void Initialize() = 0;

			coord2d pos;
			Window* target;
	};

}
