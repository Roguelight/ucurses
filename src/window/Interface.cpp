#include <ucurses/window/Interface.hpp>

namespace ucurses {

	void Interface::Bind(Window* win)
	{
		if (win->interface != nullptr)
			delete win->interface;

		win->interface = this;
	}
}
