// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Window.hpp>
#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace gui {

	Window::Window(coord2d size, coord2d position) : std(false) 
	{
        GlobalLogger::log(TRACE,"Win") << "Initialising ncurses application Window" << Sentinel::END;
        H_Window = newwin(size.y, size.x, position.y, position.x);
        keypad(H_Window, TRUE);
	}
    
    Window::Window() : std(true), title("Main")
    {
        GlobalLogger::log(TRACE,"Win") << "Initialising ncurses stdscr Window" << Sentinel::END;
        H_Window = stdscr;
        keypad(H_Window, TRUE);
        printBorder();          // Call printBorder() in constructor because stdscreen doesnt get updated
        setPosition(1,1);
        print(title);
        printGuiCommands();
    }

    Window::~Window()
	{
        if (!std)
        {
            GlobalLogger::log(TRACE,"Win") << "Destroying default ncurses application Window" << Sentinel::END;
            delwin(H_Window);
        }
        else
            GlobalLogger::log(TRACE,"Win") << "Window is stdscr, not touching pointer in destructor!" << Sentinel::END;
	}

    void Window::printCommands()
    {
        setPosition(2, getSize().y - 2);
    }

    void Window::Clear()
    {
        Commands.Clear();
        Components.RemoveAll();
    }
    
    void Window::printGuiCommands()
    {
        printCommands(); // Move to appropriate location (bottom left)
        attributeOn(A_REVERSE);
        print("Tab:");
        attributeOff(A_REVERSE);
        print(" Switch Active Window ");
        attributeOn(A_REVERSE);
        print("F1:");
        attributeOff(A_REVERSE);
        print(" Close Application");
    }

    void Window::addCommand(int key, delegate func)
    {
        Commands.Add(key,func);
    }

    /* Update */

    void Window::Update()
    {
        GlobalLogger::log(TRACE,"Win") << "Updating window -> " << title << Sentinel::END;
        werase(getHandle());
        printBorder();
        setPosition(2,0);
        print(title);
        Components.Update();
    }
	
    void Window::printBorder()
    {
        GlobalLogger::log(TRACE,"Win") << "Rendering border -> " << title << Sentinel::END;
        box(H_Window, '|', '-');
    }

    /* Construction */

    void Window::resize(coord2d size, coord2d position)
    {
        if (!std)
        {
            GlobalLogger::log(TRACE,"Win") << "Resizing window-> " << title << Sentinel::END;
            delwin(H_Window);
        }
        else
            GlobalLogger::log(WARNING,"Win") << "Tried to resize ncurses stdscr!" << Sentinel::END;
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
        coord2d curpos = getPos();
        wmove(H_Window, curpos.y + y, curpos.x + x);
    }

    void Window::print(string inString)
    {
        waddstr(H_Window, inString.c_str());
    }
            
    void Window::setPosition(coord x, coord y)
    {
        GlobalLogger::log(TRACE,"Win") << "Setting position: " << x << ", " << y << Sentinel::END;
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
        mvwchgat(H_Window, row, 0, -1, A_REVERSE, S_Colors->Get("BW"), NULL);
    }

    void Window::highlightColumn(coord column)
    {
        mvwchgat(H_Window, 0, column, -1, A_REVERSE, S_Colors->Get("Inverse"), NULL);
    }    

    void Window::highlightWord(coord2d wordpos, int size)
    {
        mvwchgat(H_Window, wordpos.y + 1, wordpos.x, size, A_REVERSE, S_Colors->Get("Inverse"), NULL);
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

    coord2d Window::getPos() const
    {
        coord2d pos;
        getyx(H_Window, pos.y, pos.x);
        return pos;
    }

}}
