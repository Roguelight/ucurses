// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Menu.hpp>
#include <ctk/file/Directory.hpp>

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

	void Menu::showHelp()
	{
		addTip("j: Down ");
		addTip("k: Up ");
	}

	void Menu::Draw()
	{
        int longest = getLongestItem();
		for (auto& item : items)
		{
            if (padding)
            {
                int diff = longest - item.length();
                if (diff >= 2)
                {
			        print(std::string(diff / 2, ' '));
                }
            }
            print(item);
            
			setCursor(0, getCursor().y + 1);
		}

		if (selection != NOSELECT)
		{
			highlightWord(coord2d(0, selection), longest, highlightColor, A_BOLD);
		}
	}

	void Menu::selectNext()
	{
		menu_template<std::string>::selectNext();
		if (onRefresh)
			onRefresh();
	}
    
    void Menu::setDirectory(const std::string& inString)
	{
		ctk::file::Directory dir(inString);
		dir.copyContents(items);

		if (!(items.empty()))
			selection = 0;
		else
			selection = -1;
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
    
    void Menu::setPadding(bool b)
    {
        padding = b; 
    }

    int Menu::getLongestItem()
    {
        int counter = 0;
        for (auto& item : items)
            if (item.length() > counter)
                counter = item.length();
        return counter;
    }

    void Menu::alignMiddle()
    {
        position.x -= getLongestItem() / 2;
    }
}
