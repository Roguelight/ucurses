// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Menu.hpp>


namespace ncursespp { namespace gui {

	Menu::Menu()  
	{
        selection = 0;
        items.reserve(40);
	}

    Menu::Menu(coord2d size, coord2d position) : Window(size,position)
    {
        selection = 0;
        items.reserve(40);
    }

    void Menu::Update()
    {
        Window::Update();
        coord xcenter = (getSize().x / 2) - 4;
        for (auto& item : items)
        {
            move(coord2d(xcenter, getPos().y + 1));
            print(item);
        }
        int size = getItem(selection).length();
        highlightWord(coord2d(xcenter, selection), size);
    }

    void Menu::addItem(string label)
    {
        index next = items.size();
        GlobalLogger::log(TRACE) << "Adding item " << label << " to menu at index: " << next <<  Sentinel::END;
        items.push_back(label);
    }

    string& Menu::getItem(index id)
    {
        if (id >= 0 && id < items.size())
        {
            return items.at(id);
        }
        else
            GlobalLogger::log(WARNING) << "Please specify index in range" << Sentinel::END;
    }

}}
