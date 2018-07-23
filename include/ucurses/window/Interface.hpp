#pragma once
#include <ucurses/window/Window.hpp>

namespace ucurses {

	class Interface
	{
		public:

			Interface(coord x = 0, coord y = 0);
			virtual void Bind(Window* win);
			virtual void Update() {}

			Window* getTarget();

		protected:

			virtual void Initialize() = 0;

			Window* target;
			coord2d pos;
	};

}
