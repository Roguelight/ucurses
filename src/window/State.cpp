#include <ucurses/window/State.hpp>

namespace ucurses {

	void State::Bind(Window* target)
	{
		this->target = target;
		Initialize();
	}
}
