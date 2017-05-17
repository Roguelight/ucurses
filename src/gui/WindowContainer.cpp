// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/WindowContainer.hpp>

namespace ucurses { namespace gui {

    WindowContainer::WindowContainer()
    {
        GlobalLogger::log(TRACE,"WinMap") << "Constructing smart window container" << Sentinel::END;
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
        GlobalLogger::log(TRACE,"WinMap") << "Adding new window to ucurses container with ID: " << ID <<  Sentinel::END;
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
            GlobalLogger::log(TRACE,"WinMap") << "Failed to find window. ID " << ID << " not valid" <<  Sentinel::END;
    }

    void WindowContainer::Remove(string ID)
    {
        GlobalLogger::log(TRACE,"WinMap") << "Removing window from ucurses GUI storage with ID: " << ID <<  Sentinel::END;
        auto win = M_Windows.find(ID);
        if (win != M_Windows.end())
        {
            delete win->second;
            win->second = nullptr;
            M_Windows.erase(win);
        }
        else
            GlobalLogger::log(TRACE,"WinMap") << "Couldn't find window to erase with ID: " << ID <<  Sentinel::END;
    }

    void WindowContainer::RemoveAll()
    {
        for (auto& element : M_Windows)
        {
            delete element.second;
            element.second = nullptr;
        }
    }

    void WindowContainer::UpdateActive()
    {
        // Highlight active window
        Window* active = getActive();
        if (active) // Only update active window; this means a windows display will not change unless active
        {
            active->Update();
            active->highlightRow(1);
        }
    }

    void WindowContainer::UpdateAll()
    {
        for (auto& element : M_Windows)
            element.second->Update();

        // Highlight active window
        Window* active = getActive();
        active->Update();
        if (active) 
            active->highlightRow(0);
    }

    void WindowContainer::Refresh()
    {
        GlobalLogger::log(TRACE, "WindowContainer") << "Refreshing windows" << Sentinel::END;

        for (auto& element : M_Windows)
            wnoutrefresh(element.second->getHandle());
        
    }

    void WindowContainer::Next()
    {
        if (M_Windows.empty())
        {
            GlobalLogger::log(WARNING, "WindowContainer") << "Window map empty, Next() called, doing nothing" << Sentinel::END;
            active.second = nullptr;
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
        if (active.second != nullptr)
            active.second->Commands.Parse(input);
        else
            GlobalLogger::log(WARNING, "WindowContainer::") << "Active window is null, cannot handle command" << Sentinel::END;
    }


}}
