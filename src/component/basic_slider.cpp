#include <component/basic_slider.hpp>
#include <fstream>

namespace ucurses { 

	basic_slider::basic_slider() : value(0.0f)
	{

	}
	
	basic_slider::basic_slider(const std::string& name) : value(0.0f), subject(name)
	{
	
	}

	void basic_slider::increment()
    {
		if ((value + 1.0f) <= 100.f)
			value += 1.0f;
	}

	void basic_slider::decrement()
	{    
		if ((value - 1.0f) >= 0.0f)
			value -= 1.0f;
	}
}
