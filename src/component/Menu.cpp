// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Menu.hpp>

namespace ucurses {

    Menu::Menu(coord x, coord y, Window* host) : Component(x, y, host) 
    {
        selection = NONE;
        items.reserve(24);
        bindDefault();
    }

    void Menu::bindDefault()
    {
        addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
        addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
        addTip("j: Down ");
        addTip("k: Up ");
    }

    void Menu::Update()
    {
		setCursor();
		H_Window->setColor(color);

        for (auto& item : items)
        {
            setCursor(0, getCursor().y + 1);
            print(item);
        }

        if (selection != NONE)
        {
            int size = getSelectedItem().length();
            highlightWord(coord2d(0, selection), size, highlightColor, A_BOLD);
        }
		H_Window->unsetColor(color);
    }
    
    string Menu::getSelectedItem()
    {
        if (selection != NONE) 
            return getItem(selection); 
        else
            return string("");
    }

    index Menu::getSelectedIndex()
    {
        return selection;
    }

    void Menu::addItem(const string& label)
    {
		selection = 0;
        items.push_back(label);
    }

    void Menu::removeAll()
    {
        items.clear(); 
    }

    string& Menu::getItem(index id) 
    {
        if (id < items.size())
        {
            return items[id];
        }
    }

    void Menu::selectNext()
    {
        if (!(items.empty()))
        {
            if (!last()) 
                ++selection;
        }
        else
            selection = NONE;
    }
    
    void Menu::selectPrevious()
    {
        if (!(items.empty()))
        {
            if (selection > 0)
                --selection;
        }
        else
            selection = NONE;
    }

    void Menu::removeItem(index id)
    {
        if (selection != NONE)
        {
            if (last()) 
                selection--;

            items.erase(items.begin() + id);

            if (items.empty())
                selection = NONE;
        }
    }
    
    void Menu::removeSelectedItem()
    {
        index id = getSelectedIndex();
        removeItem(id);
    }

}
