// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/Window.hpp>
#include <ucurses/app/GUI.hpp>

namespace ucurses {

	Window::Window(coord2d size, coord2d position, ColorContainer* Handle) : std(false) 
	{
        GlobalLogger::instance().log(TRACE) << "Initialising ucurses app Window" << Sentinel::END;
        H_Window = newwin(size.y, size.x, position.y, position.x);
        keypad(H_Window, TRUE);
	}
    
    Window::Window(ColorContainer* Handle) : std(true), title("Main")
    {
        GlobalLogger::instance().log(TRACE) << "Initialising UCurses stdscr Window" << Sentinel::END;
        H_Window = stdscr;
        keypad(H_Window, TRUE);
        CommandMap.Add("Tab:", " Switch Active ");
        CommandMap.Add("F1:", " Close Application ");
    }

    Window::~Window()
	{
        if (!std)
        {
            GlobalLogger::instance().log(TRACE) << "Destroying UCurses app Window " << title <<  Sentinel::END;
            delwin(H_Window);
        }
        else
            GlobalLogger::instance().log(TRACE) << "Window is stdscr, not touching pointer in destructor!" << Sentinel::END;
	}

    void Window::printCommands()
    {
        setPosition(2, getSize().y - 2);
        for (auto& it : CommandMap.tips)
        {
            attributeOn(A_REVERSE);
            print(it.first);
            attributeOff(A_REVERSE);
            print(it.second);
        }
    }

    void Window::Clear()
    {
        GlobalLogger::instance().log(TRACE) << "Clearing out window component array for " << title << Sentinel::END;
        Commands.Clear();
        CommandMap.Clear();
        Components.RemoveAll();
    }

    void Window::addComponent(Component* component)
    {
        GlobalLogger::instance().log(TRACE) << "Adding component to window " << title << Sentinel::END;
        Components.Add(component);
    }
    
    void Window::addCommand(int key, delegate func)
    {
        GlobalLogger::instance().log(TRACE) << "Adding command to window " << title << Sentinel::END;
        Commands.Add(key,func);
    }

    void Window::addTip(string keyID, string funcID)
    {
        CommandMap.Add(keyID, funcID);
    }

    /* Update */

    void Window::Update()
    {
        werase(H_Window);
        printBorder();
        setPosition(2,0);
        print(title);
        printCommands();
        Components.Update();
    }
	
    void Window::printBorder()
    {
        box(H_Window, '|', '-');
    }

    /* Construction */

    void Window::resize(coord2d size, coord2d position)
    {
        if (!std)
        {
            GlobalLogger::instance().log(TRACE) << "Resizing window-> " << title << Sentinel::END;
            delwin(H_Window);
        }
        else
            GlobalLogger::instance().log(TRACE) << "Tried to resize ncurses stdscr!" << Sentinel::END;
    }

    void Window::EnableColor(ColorContainer* s_ptr) 
    {
        S_Colors = s_ptr;
    }

    void Window::setTitle(string s)
    {
        title = s;        
    }

    /* Manipulation */

    void Window::move(coord x, coord y)
    { 
        coord2d curpos = getPosition();
        wmove(H_Window, curpos.y + y, curpos.x + x);
    }

    void Window::print(string inString)
    {
        waddstr(H_Window, inString.c_str());
    }
            
    void Window::setPosition(coord x, coord y)
    {
        wmove(H_Window, y, x);
    }
            
    // Attributes        
    void Window::setAttributes(int attributes)      
    {
        wattrset(H_Window, attributes); 
    }

    void Window::attributeOn(int attributes)
    { 
        wattron(H_Window, attributes);  
    } 

    void Window::attributeOff(int attributes)
    { 
        wattroff(H_Window, attributes); 
    }

    // Highlighting

    void Window::highlightRow(coord row)
    {
        mvwchgat(H_Window, row, 0, -1, A_REVERSE, COLOR_PAIR(0), NULL);
    }

    void Window::highlightColumn(coord column)
    {
        mvwchgat(H_Window, 0, column, -1, A_REVERSE, COLOR_PAIR(0), NULL);
    }    

    void Window::highlightWord(coord2d wordpos, int size)
    {
        mvwchgat(H_Window, wordpos.y + 1, wordpos.x, size, A_REVERSE, COLOR_PAIR(0), NULL);
    }

    /* Retrieval methods */
    
    coord2d Window::getSize() const
    {
        coord2d size;
        getmaxyx(H_Window, size.y, size.x);
        return size;
    }

    coord2d Window::getMiddle() const
    {
        coord2d size = getSize(); 
        coord2d middle(size.x / 2, size.y / 2);
        return middle;
    }
    
    WINDOW* Window::getHandle() const
    { 
        return H_Window;  
    }

    string Window::getTitle() const
    {
        return title;     
    }

    coord2d Window::getPosition() const
    {
        coord2d pos;
        getyx(H_Window, pos.y, pos.x);
        return pos;
    }

}
