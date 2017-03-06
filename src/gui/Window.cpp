// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Window.hpp>
#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace gui {

	Window::Window(coord2d size, coord2d position) : std(false)
	{
        GlobalLogger::log(TRACE,"NCursespp::Window") << "Initialising ncurses application Window" << Sentinel::END;
        H_Window = newwin(size.y, size.x, position.y, position.x);
        keypad(H_Window, TRUE);
        addBorder();
        initCommands();
	}
    
    Window::Window() : std(true)
    {
        GlobalLogger::log(TRACE,"NCursespp::Window") << "Initialising ncurses stdscr Window" << Sentinel::END;
        H_Window = stdscr;
        keypad(H_Window, TRUE);
        addBorder();
        initCommands();
        setTitle("Stdscr");
    }

	Window::~Window()
	{
        if (!std)
        {
            GlobalLogger::log(TRACE,"NCursespp::Window") << "Destroying default ncurses application Window" << Sentinel::END;
            delwin(H_Window);
        }
        else
            GlobalLogger::log(TRACE,"NCursespp::Window") << "Window is stdscr, not touching pointer in destructor!" << Sentinel::END;
	}

    void Window::setTitle(string s)
    { 
        title = s;        
    }

    void Window::Update()
    {
        setAttributes(A_NORMAL);
        move(coord2d(1,1));
        print(title);
    }

    void Window::resize(coord2d size, coord2d position)
    {
        if (!std)
        {
            GlobalLogger::log(WARNING,"NCursespp::Window") << "Resizing window" << Sentinel::END;
            delwin(H_Window);
        }
        else
        {
            H_Window = newwin(size.y, size.x, position.y, position.x);
            GlobalLogger::log(WARNING,"NCursespp::Window") << "Tried to resize ncurses stdscr, creating sub window instead" << Sentinel::END;
        }
    }

    coord2d Window::getSize() const
    {
        coord2d size;
        getmaxyx(H_Window, size.y, size.x);
        return size;
    }
    
    coord2d Window::getPos() const
    {
        coord2d pos;
        getyx(H_Window, pos.y, pos.x);
        return pos;
    }

    void Window::addBorder()
    {
        GlobalLogger::log(TRACE,"NCursespp::Window") << "Creating border for Window" << Sentinel::END;
        box(H_Window, '|', '-');
    }

    void Window::highlightRow(coord row)
    {
        mvwchgat(H_Window, row, 0, -1, A_STANDOUT, S_Colors->Get("Inverse"), NULL);
    }

    void Window::highlightColumn(coord column)
    {
        mvwchgat(H_Window, 0, column, -1, A_STANDOUT, S_Colors->Get("Inverse"), NULL);
    }    

    void Window::highlightWord(coord2d wordpos, int size)
    {
        mvwchgat(H_Window, wordpos.y + 1, wordpos.x, size, A_STANDOUT, S_Colors->Get("Inverse"), NULL);
    }

    WindowContainer::WindowContainer()
    {
        GlobalLogger::log(TRACE,"NCursespp::WindowContainer") << "Constructing smart window container" << Sentinel::END;
    }

    WindowContainer::~WindowContainer()
    {
        for (auto& element : M_Windows)
        {
            delete element.second;
            element.second = nullptr;
        }
    }
    
    void WindowContainer::Add(string ID, Window* win)
    {
        GlobalLogger::log(TRACE,"NCursespp::WindowContainer") << "Adding new window to ncursespp container with ID: " << ID <<  Sentinel::END;
        win->setTitle(ID);
        win->EnableColor(&Colors);
        active.first = ID;
        active.second = win;
        M_Windows.insert(std::pair<string, Window*>(ID, win));
    }

    Window* WindowContainer::Get(string ID) const
    {
        auto window = M_Windows.find(ID); 
        if (window != M_Windows.end())
            return window->second;
        else
            GlobalLogger::log(TRACE,"NCursespp::WindowContainer") << "Failed to find window. ID " << ID << " not valid" <<  Sentinel::END;
    }

    void WindowContainer::Remove(string ID)
    {
        GlobalLogger::log(TRACE,"NCursespp::WindowContainer") << "Removing window from ncursespp GUI storage with ID: " << ID <<  Sentinel::END;
        auto win = M_Windows.find(ID);
        if (win != M_Windows.end())
        {
            delete win->second;
            win->second = nullptr;
            M_Windows.erase(win);
        }
        else
            GlobalLogger::log(TRACE,"NCursespp::WindowContainer") << "Couldn't find window to erase with ID: " << ID <<  Sentinel::END;
    }

    void WindowContainer::Update()
    {
        for (auto& element : M_Windows)
            element.second->Update();
    }

    void WindowContainer::Refresh()
    {
        for (auto& element : M_Windows)
        {
            wnoutrefresh(element.second->getHandle());
        }
    }

    void WindowContainer::Next()
    {
        if (M_Windows.empty())
        {
            GlobalLogger::log(WARNING, "WindowContainer") << "Window map empty, Next() called, doing nothing" << Sentinel::END;
            active.first = nullptr;
        }
        else
        {
            GlobalLogger::log(TRACE, "WindowContainer") << "Selecting next active window: ";
            auto activeit = M_Windows.find(active.first);
            if ((++activeit) == M_Windows.end())
            {
                active.first = M_Windows.begin()->first;
                active.second = M_Windows.begin()->second;
                GlobalLogger::log(TRACE, "WindowContainer") << active.first << Sentinel::END;
            }
            else
            {
                active.first = activeit->first;
                active.second = activeit->second;
                GlobalLogger::log(TRACE, "WindowContainer") << active.first << Sentinel::END;
            }
        }
    }

    void WindowContainer::Parse(int input)
    { 
        GlobalLogger::log(TRACE, "WindowContainer") << "Delegating command to active window " << active.first <<  Sentinel::END;
        active.second->Commands.Parse(input);
    }


}}
