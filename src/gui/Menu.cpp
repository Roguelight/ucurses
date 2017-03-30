// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Menu.hpp>
#include <ncursespp/gui/Window.hpp>


namespace ncursespp { namespace gui {

    Menu::Menu(coord x, coord y, Window* host) : Component(x, y, host) 
    {
        setSize(40,15);
        GlobalLogger::log(TRACE,"Menu") << "Inititalising new menu with selection at index -1" << Sentinel::END;
        selection = NONE;
        items.reserve(24);
    }

    void Menu::bindDefault()
    {
        addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
        addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
    }

    void Menu::printCommands()
    {
        GlobalLogger::log(TRACE,"Menu") << "Printing commands:" << Sentinel::END;
        printPosition();
        attributeOn(A_REVERSE);
        print("Enter:");
        attributeOff(A_REVERSE);
        print(" Select ");
    }
    
    void Menu::Update()
    {
        printCommands();
        coord xcenter = getMiddle().x - 4;
        coord ymargin = 2;
        
        GlobalLogger::log(TRACE,"Menu") << "Updating menu, redrawing items at center: " << xcenter << Sentinel::END;
        setPosition(xcenter, ymargin); //Initial position

        for (auto& item : items)
        {
            setPosition(xcenter, getPos().y + 1);
            GlobalLogger::log(TRACE,"Menu") << "Printing item: " << item << " at position: ";
            GlobalLogger::log(TRACE,"Menu") << getPos().x << ", " << getPos().y << Sentinel::END;

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
        GlobalLogger::log(TRACE,"Menu") << "Adding item " << label << " to menu at index: " << selection <<  Sentinel::END;
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
            GlobalLogger::log(WARNING,"Menu") << "Fetching item at index: " << id << Sentinel::END;
            return items.at(id);
        }
        else
            GlobalLogger::log(WARNING,"Menu") << "Please specify index in range" << Sentinel::END;
    }

    void Menu::selectNext()
    {
        if (!(items.empty()))
        {
            if (last()) 
            {
                GlobalLogger::log(TRACE,"Menu") << "At last element, not modifying selection" << Sentinel::END;
            }
            else
            {
                ++selection;
                GlobalLogger::log(TRACE,"Menu") << "Selecting next item at index: " << selection << Sentinel::END;
            }
        }
        else
        {
            GlobalLogger::log(TRACE,"Menu") << "Menu empty, selecting 0" << Sentinel::END;
            selection = -1;
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
