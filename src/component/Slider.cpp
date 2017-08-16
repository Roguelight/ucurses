#include <ucurses/component/Slider.hpp>


namespace ucurses { 

	Slider::Slider(coord x, coord y, Window* host) : Component(x, y, host)
	{
		setHighlight(1);
		bindDefault();
	}

	void Slider::bindDefault()
	{
		addCommand('l', bind( &Slider::increment, this));
		addCommand('h', bind( &Slider::decrement, this));
	}

	void Slider::Draw()
	{
		//20 characters long
		std::string slider("|-----------------------|");
		
		print(subject + ": " + slider);
		highlightWord(coord2d(subject.length() + 3,-1), value / 4, highlightColor, A_BOLD);
	}


}
