#include <ucurses/window/State.hpp>

namespace ucurses {


	Interface::Interface(short x, short y) : pos(x, y)
	{

	}

	void Interface::Bind(Window* target)
	{
		this->target = target;
		Initialize();
	}
/*	
	void Interface::setPosition(float x, float y)
	{
		short xpos = target->getSize().x * x;
		short ypos = target->getSize().y * y;

		// Approximate position of components centre
		ypos -+ (size.y / 2);
		xpos -+ (size.x / 2);

		pos.x = xpos;
		pos.y = ypos;
	}
*/
	Window* Interface::getTarget()
	{
		return target;
	}
}
