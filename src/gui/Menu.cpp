// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Menu.hpp>


namespace ncursespp { namespace gui {

    Menu::Menu(coord x, coord y, Window* host) : Component(size, pos, host) 
    {
        setSize(40,20);
        GlobalLogger::log(TRACE, "NCursespp::Menu") << "Inititalising new menu with selection at index -1" << Sentinel::END;
        selection = NONE;
        items.reserve(24);
    }

    void Menu::bindDefault()
    {
        addCommand('a', bind( &Menu::addItem, this, string("Connect")));   // Test add item
        addCommand(KEY_BACKSPACE, bind( &Menu::removeSelectedItem, this)); // Remove highlighted item
        addCommand('j', bind( &Menu::selectNext, this));                   // Move down menu 
        addCommand('k', bind( &Menu::selectPrevious, this));               // Move up Menu 
        addCommand(10, bind( &Menu::Select, this));                        // Select highlighted item <Enter>
    }

    void Menu::printCommands()
    {
        commandPrintPos();
        attributeOn(A_REVERSE);
        print("Enter:");
        attributeOff(A_REVERSE);
        print(" Select ");
    }
    
    void Menu::Update()
    {
        printCommands();
        GlobalLogger::log(TRACE, "NCursespp::Menu") << "Updating menu, redrawing items" << Sentinel::END;
        coord xcenter = getMiddle().x - 4;
        coord ymargin = 2;
        setPosition(xcenter, ymargin); //Initial position

        for (auto& item : items)
        {
            GlobalLogger::log(TRACE, "NCursespp::Menu") << "Printing item: " << item <<  Sentinel::END;
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
        GlobalLogger::log(TRACE,"NCursespp::Menu") << "Adding item " << label << " to menu at index: " << selection <<  Sentinel::END;
        items.push_back(label);
    }

    string& Menu::getItem(index id)
    {
        if (id < items.size())
        {
            GlobalLogger::log(WARNING, "NCursespp::Menu") << "Fetching item at index: " << id << Sentinel::END;
            return items.at(id);
        }
        else
            GlobalLogger::log(WARNING, "NCursespp::Menu") << "Please specify index in range" << Sentinel::END;
    }

    void Menu::selectNext()
    {
        if (!(items.empty()))
        {
            if (last()) 
            {
                GlobalLogger::log(TRACE, "NCursespp::Menu") << "At last element, not modifying selection" << Sentinel::END;
            }
            else
            {
                ++selection;
                GlobalLogger::log(TRACE, "NCursespp::Menu") << "Selecting next item at index: " << selection << Sentinel::END;
            }
        }
        else
        {
            GlobalLogger::log(TRACE, "NCursespp::Menu") << "Menu empty, selecting 0" << Sentinel::END;
            selection = -1;
        }
    }
    
    void Menu::selectPrevious()
    {
        if (!(items.empty()))
        {
            if (selection <= 0)
            {
                GlobalLogger::log(TRACE, "NCursespp::Menu") << "At first element, not modifying selection" << Sentinel::END;
            }
            else
            {
                --selection;
                GlobalLogger::log(TRACE, "NCursespp::Menu") << "Decreasing selection to index: " << selection << Sentinel::END;
            }
        }
        else
        {
            GlobalLogger::log(TRACE, "NCursespp::Menu") << "Menu empty, selecting 0" << Sentinel::END;
            selection = NONE;
        } 
    }

    void Menu::removeItem(index id)
    {
        if (selection != NONE)
        {
            GlobalLogger::log(TRACE, "NCursespp::Menu") << "Removing item at index " << id << Sentinel::END;
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
        GlobalLogger::log(TRACE, "NCursespp::Menu") << "Removing selected item" << Sentinel::END;
        removeItem(id);
    }

}}
