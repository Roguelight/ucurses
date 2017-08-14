#include <component/Slider.hpp>


namespace ucurses { 

	Slider(coord x, coord y, Window* host) : Component(x, y, host), value(0.0f)
	{

	}

    void Slider::increment()
    {
        if ((value + 1.0f) < 100)
            value += 1.0f;
    }
    
    void Slider::decrement()
    {    
        if ((value - 1.0f) > 0)
            value -= 1.0f;
    }

    void Slider::bindDefault()

}
