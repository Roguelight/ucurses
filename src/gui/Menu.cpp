// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/Menu.hpp>
#include <ucurses/gui/Window.hpp>


namespace ucurses { namespace gui {

    Menu::Menu(coord x, coord y, Window* host) : Component(x, y, host) 
    {
        setSize(40,15);
        selection = NONE;
        items.reserve(24);
    }

    void Menu::bindDefault()
    {
        addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
        addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
        addTip("j:", " Down ");
        addTip("k:", " Up ");
    }

    void Menu::Update()
    {
        coord xcenter = getMiddle().x - 4;
        coord ymargin = 2;
        
        setPosition(xcenter, ymargin); //Initial position

        for (auto& item : items)
        {
            setPosition(xcenter, getPos().y + 1);
            print(item);
        }

        if (selection != NONE)
        {
            int size = getSelectedItem().length();
            highlightWord(coord2d(xcenter, selection + ymargin), size);
        }
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

    void Menu::addItem(string label)
    {
        selection  = items.size();
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
            return items.at(id);
        }
        else
            H_Window->getLogger().log(WARNING) << "Please specify index in range" << Sentinel::END;
    }

    void Menu::selectNext()
    {
        if (!(items.empty()))
        {
            if (last()) 
            {
                H_Window->getLogger().log(TRACE) << "At last element, not modifying selection" << Sentinel::END;
            }
            else
            {
                ++selection;
                H_Window->getLogger().log(TRACE) << "Selecting next item at index: " << selection << Sentinel::END;
            }
        }
        else
        {
            H_Window->getLogger().log(TRACE) << "Menu empty, selecting 0" << Sentinel::END;
            selection = NONE;
        }
    }
    
    void Menu::selectPrevious()
    {
        if (!(items.empty()))
        {
            if (selection <= 0)
            {
                GlobalLogger::log(TRACE,"Menu") << "At first element, not modifying selection" << Sentinel::END;
            }
            else
            {
                --selection;
                GlobalLogger::log(TRACE,"Menu") << "Decreasing selection to index: " << selection << Sentinel::END;
            }
        }
        else
        {
            GlobalLogger::log(TRACE,"Menu") << "Menu empty, selecting 0" << Sentinel::END;
            selection = NONE;
        } 
    }

    void Menu::removeItem(index id)
    {
        if (selection != NONE)
        {
            GlobalLogger::log(TRACE,"Menu") << "Removing item at index " << id << Sentinel::END;
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
        GlobalLogger::log(TRACE,"Menu") << "Removing selected item" << Sentinel::END;
        removeItem(id);
    }

}}
