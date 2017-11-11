#include <ucurses/window/Interface.hpp>

namespace ucurses {

	void Interface::Bind(Window* target)
	{
		this->target = target;
		Initialize();
	}
}
