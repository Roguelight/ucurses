// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/SliderMenu.hpp>

namespace ucurses {

	SliderMenu::SliderMenu(Window* host, coord x, coord y) : Component(host, x, y) 
	{
		//bindDefault();
	}

	void SliderMenu::bindDefault()
	{
		addCommand('j', bind( &SliderMenu::selectNext, this));                   // Move down menu 
		addCommand('k', bind( &SliderMenu::selectPrevious, this));               // Move up Menu 
		addCommand('l', bind( &SliderMenu::incrementActive, this));
		addCommand('h', bind( &SliderMenu::decrementActive, this));
	}

	void SliderMenu::Process(int input)
	{
		switch (input)
		{
			case 'j':
				selectNext();
				break;
			case 'k':
				selectPrevious();
				break;
			case 'l':
				incrementActive();
				break;
			case 'h':
				decrementActive();
				break;
		}
	}

	void SliderMenu::incrementActive()
	{
		items[selection].increment();
	}
	
	void SliderMenu::decrementActive()
	{
		items[selection].decrement();
	}

	void SliderMenu::showHelp()
	{
		addTip("j: Down ");
		addTip("k: Up ");
	}

	void SliderMenu::Draw()
	{
		std::string slider("|-----------------------|");

		for (auto& item : items)
		{
			print(item.getSubject() + ": " + slider);
            if (print_numeric)
                print(" " + std::to_string(item.getValue()));
			highlightWord(coord2d(item.getSubject().length() + 3, getCursor().y), item.getPercentage() / 4, highlightColor, A_BOLD);
			setCursor(0, getCursor().y + 1);
		}
		
		if (selection != NOSELECT)
		{
			int size = getSelectedItem().getSubject().length();
			highlightWord(coord2d(0, selection), size, highlightColor, A_STANDOUT);
		}
	}
}
