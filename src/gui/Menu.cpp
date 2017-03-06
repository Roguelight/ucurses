// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Menu.hpp>


namespace ncursespp { namespace gui {

    Menu::Menu(coord2d size, coord2d position) : Window(size,position) 
    {
        GlobalLogger::log(TRACE, "NCursespp::Menu") << "Inititalising new menu with selection at index -1" << Sentinel::END;
        selection = NONE;
        setTitle("Menu");
        items.reserve(40);
        addCommands();
    }

    void Menu::addCommands()
    {
        Commands.Add(bind( &Menu::addItem, this, string("Connect")), 'a');   // Test add item
        Commands.Add(bind( &Menu::removeSelectedItem, this), KEY_BACKSPACE); // Remove highlighted item
        Commands.Add(bind( &Menu::selectNext, this), 'j');                   // Move down menu 
        Commands.Add(bind( &Menu::selectPrevious, this), 'k');               // Move up Menu 
        Commands.Add(bind( &Menu::Select, this),  10);                       // Select highlighted item <Enter>
    }
    
    /*
     * Prints all items in a menu and highlights selected.
     * Considered only changing the highlight of the items
     * in update but makes the loop more unpredictable
     */
    void Menu::Update()
    {
        werase(getHandle());
        Window::Update();
        GlobalLogger::log(TRACE, "NCursespp::Menu") << "Updating menu, redrawing items" << Sentinel::END;
        coord xcenter = (getSize().x / 2) - 4;
        int size = getItem(selection).length();
        move(coord2d(xcenter, 1)); //Initial position

        for (auto& item : items)
        {
            move(coord2d(xcenter, getPos().y + 1));
            print(item);
            wclrtoeol(getHandle());
        }

        highlightWord(coord2d(xcenter, selection + 1), size);
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
            items.erase(items.begin() + id);
            if (last()) 
                selection--;
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
