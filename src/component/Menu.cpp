// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Menu.hpp>

namespace ucurses {

	Menu::Menu(Window* host, coord x, coord y) : Component(host, x, y) 
	{
		bindDefault();
	}

	void Menu::bindDefault()
	{
		addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
		addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
	}

	void Menu::showHelp()
	{
		addTip("j: Down ");
		addTip("k: Up ");
	}

	void Menu::Draw()
	{
		for (auto& item : items)
		{
			print(item);
			setCursor(0, getCursor().y + 1);
		}

		if (selection != NOSELECT)
		{
			int size = getSelectedItem().length();
			highlightWord(coord2d(0, selection), size, highlightColor, A_BOLD);
		}
	}
}
