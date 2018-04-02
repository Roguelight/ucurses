// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Menu.hpp>

namespace ucurses {

	Menu::Menu(Window* host, coord x, coord y) : Component(host, x, y)
	{
		//bindDefault();
	}

	void Menu::bindDefault()
	{
		addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
		addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
	}

	void Menu::Process(int input)
	{
		switch (input)
		{
			case 'j':
				selectNext();
				break;
			case 'k':
				selectPrevious();
				break;
            case 10:
                if (onSelect)
                    onSelect();
                break;
		}
	}

    void Menu::alignMiddle()
    {
        position.x -= 8;
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

	void Menu::selectNext()
	{
		menu_template<std::string>::selectNext();
		if (onRefresh)
			onRefresh();
	}
			
	void Menu::selectPrevious()
	{
		menu_template<std::string>::selectPrevious();
		if (onRefresh)
			onRefresh();
	}
/*
	void Menu::addItem(const std::string& label)
	{
		menu_template<std::string>::addItem(label);
		short xsize;

		if (label.length() > size.x)
			xsize = label.length();
		else
			xsize = size.x;

		setSize(xsize, items.size());
	}
*/
}
