// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/WindowContainer.hpp>
#include <algorithm>

namespace ucurses { 

    WindowContainer::WindowContainer()
    {
        GlobalLogger::log(TRACE) << "Constructing smart window container" << Sentinel::END;
        active = NONE;
        M_Windows.reserve(5);
    }

    WindowContainer::~WindowContainer()
    {

    }
    
    Window* WindowContainer::Create(coord2d size, coord2d pos, bool deletable)
    {
        active = M_Windows.size();
        M_Windows.emplace_back(size, pos, deletable);

        if (deletable)
            M_Windows[active].addCommand(KEY_F(2), std::bind( &WindowContainer::RemoveActive, this));

        return &(M_Windows[active]);
    }
    
    Window* WindowContainer::Create(bool deletable)
    {
        active = M_Windows.size();
        coord2d size;
        getmaxyx(stdscr, size.y, size.x);
        M_Windows.emplace_back(size, coord2d(0,0));

        if (deletable)
            M_Windows[active].addCommand(KEY_F(2), std::bind( &WindowContainer::RemoveActive, this));

        return &(M_Windows[M_Windows.size() - 1]);
    }

    const Window& WindowContainer::Get(string ID) const
    {
        auto it = std::find(M_Windows.begin(), M_Windows.end(), ID);
        if (it != M_Windows.end())
            return *it;
        else
            GlobalLogger::instance().log(TRACE) << "Failed to find window. ID " << ID << " not valid" <<  Sentinel::END;
    }
                
    Window& WindowContainer::getActive() 
    {
        return M_Windows[active]; 
    }

    int WindowContainer::getInput()
    {
        if (active != NONE)
            return wgetch(getActive().getHandle());
        else
            return getch();
    }

    void WindowContainer::Remove(string ID)
    {
        GlobalLogger::instance().log(TRACE) << "Removing window from ucurses GUI storage with ID: " << ID <<  Sentinel::END;
        auto it = std::find(M_Windows.begin(), M_Windows.end(), ID);
        if (it != M_Windows.end())
        {
            M_Windows.erase(it);
        }
        else
            GlobalLogger::instance().log(WARNING) << "Couldn't find window to erase with ID: " << ID <<  Sentinel::END;
    }

    void WindowContainer::RemoveActive()
    {
        if (active != NONE)
        {
			if (M_Windows[active].deletable)
			{
            	M_Windows.erase(M_Windows.begin() + active);
            	active = NONE;
            	Next();
			}
        }
    }

    void WindowContainer::RemoveAll()
    {
        M_Windows.clear();
    }

    void WindowContainer::UpdateActive()
    {
        if (active != NONE) // Only update active window; this means a windows display will not change unless active
        {
            M_Windows[active].Update();
            M_Windows[active].highlightRow(1);
        }
        else
            GlobalLogger::instance().log(WARNING) << "There is no active window!" << Sentinel::END;
    }

    void WindowContainer::UpdateAll()
    {
        for (auto& element : M_Windows)
            element.Update();
            
        if (active != NONE) 
            M_Windows[active].highlightRow(0);
    }

    void WindowContainer::Refresh()
    {
        for (auto& element : M_Windows)
        {
            wnoutrefresh(element.getHandle());
        }
    }

    void WindowContainer::Next()
    {
        if (M_Windows.empty())
            active = NONE;
        else
            if ((++active) == M_Windows.size())
                active = 0;
    }

    void WindowContainer::Parse(int input)
    { 
        if (active != NONE)
		{
            M_Windows[active].Commands.Parse(input);
			if (M_Windows[active].callback.key == input)
				M_Windows[active].callback.execute();
		}
    }

}
