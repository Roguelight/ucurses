// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/Window.hpp>
#include <ucurses/app/UCurses.hpp>

namespace ucurses {

	UCurses* Window::ucurses = nullptr;
	ColorContainer* Window::S_Colors = nullptr;

	Window::Window(coord2d size, coord2d position, bool deletable) : deletable(deletable), callback()
	{
        H_Window = newwin(size.y, size.x, position.y, position.x);
        keypad(H_Window, TRUE);
	}
    
    Window::Window(bool deletable)  : deletable(deletable), callback()
    {
        H_Window = newwin(0,0,0,0);
        keypad(H_Window, TRUE);
    }

    Window::~Window()
	{
        delwin(H_Window);
	}

	Window* Window::subWindow(coord2d size, coord2d pos)
	{
		return ucurses->createWindow(size, pos, true);
	}

    void Window::printCommands()
    {
		coord2d size = getSize();
        setPosition(2, size.y - 2);
        for (auto& tip : tips)
        {
            print(tip);
			print("  ");
        }
        setPosition(size.x - (callback_tip.size() + 2), getSize().y - 2);
		print(callback_tip);

		if (ucurses->Help())
		{
			setPosition(2, 2);
			for (auto& tip : ucurses->getTips())
			{
				print(tip);
				print("  ");
        	}
		}
    }

    void Window::Clear()
    {
        Commands.Clear();
        tips.clear();
        Components.RemoveAll();
    }

	void Window::clearCommands()
	{
		Commands.Clear();
		tips.clear();
	}

	void Window::clearComponents()
	{
		Components.RemoveAll();
	}

    void Window::addComponent(Component* component)
    {
        Components.Add(component);
        GlobalLogger::instance().log(DEBUG) << "Successfully added component, new size is " <<
			Components.getSize() << " and capacity is " << Components.getCapacity() << Sentinel::END;
    }
    
    void Window::addCommand(int key, delegate func)
    {
        Commands.Add(key,func);
    }

	void Window::setCallback(int key, delegate func)
	{
		callback.function = func;
		callback.key = key;
	}

	void Window::disableCallback()
	{ 
		callback.disable(); 
		callback_tip.clear();
	}

	void Window::addTip(string& tip)
    {
        tips.push_back(tip);
    }

    void Window::addTip(string&& tip)
    {
        tips.push_back(tip);
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
    /*
    void Window::resize(coord2d size, coord2d position)
    {
        GlobalLogger::instance().log(TRACE) << "Resizing window -> " << title << Sentinel::END;
        delwin(H_Window);
        GlobalLogger::instance().log(WARNING) << "Tried to resize ncurses stdscr!" << Sentinel::END;
    }
    */
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
