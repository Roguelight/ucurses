#include <ucurses/component/Slider.hpp>


namespace ucurses { 

	Slider::Slider(Window* host, coord x, coord y) : Component(host, x, y)
	{
		setHighlight(1);
		//bindDefault();
	}

	void Slider::bindDefault()
	{
		addCommand('l', bind( &Slider::increment, this));
		addCommand('h', bind( &Slider::decrement, this));
	}
	
	void Slider::Process(int input)
	{
		switch (input)
		{
			case 'l':
				increment();
				break;
			case 'h':
				decrement();
				break;
		}
	}


	void Slider::Draw()
	{
		//20 characters long
		std::string slider("|-----------------------|");
		
		print(subject + ": " + slider);
		highlightWord(coord2d(subject.length() + 3,-1), value / 4, highlightColor, A_BOLD);
	}


}
