// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/WindowContainer.hpp>
#include <algorithm>

using namespace ctk::log;

namespace ucurses { 

	WindowContainer::WindowContainer()
	{
		active = NOACTIVE;
		M_Windows.reserve(5);
	}

	WindowContainer::~WindowContainer()
	{

	}

	Window* WindowContainer::Create(coord2d size, coord2d pos)
	{
		active = M_Windows.size();
		M_Windows.emplace_back(size, pos);
		return &(M_Windows[active]);
	}

	Window* WindowContainer::Create()
	{
		active = M_Windows.size();
		coord2d size;
		getmaxyx(stdscr, size.y, size.x);
		M_Windows.emplace_back(size, coord2d(0,0));
		return &(M_Windows[M_Windows.size() - 1]);
	}

	const Window& WindowContainer::Get(const std::string& ID) const
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
		if (active != NOACTIVE)
			return wgetch(getActive().getHandle());
		else
			return getch();
	}

	void WindowContainer::Remove(const std::string& ID)
	{
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
		if (active != NOACTIVE)
		{
			if (M_Windows[active].deletable)
			{
				M_Windows.erase(M_Windows.begin() + active);
				active = NOACTIVE;
				Next();
			}
		}
	}

	void WindowContainer::RemoveAll()
	{
		M_Windows.clear();
	}

	void WindowContainer::Refresh()
	{
		for (int i = 0; i < M_Windows.size(); ++i)
		{
			M_Windows[i].Update();

			/* Must highlight after update for visible effect */
			if (i == active) 
				M_Windows[i].highlightRow(0, 1, A_BOLD);

			wnoutrefresh(M_Windows[i].getHandle());
		}
	}

	void WindowContainer::ClearAll()
	{
		for (auto& win : M_Windows)
			win.ClearScreen();
	}

	void WindowContainer::Next()
	{
		if (M_Windows.empty())
			active = NOACTIVE;
		else
			if ((++active) == M_Windows.size())
				active = 0;
	}

	void WindowContainer::Process(int input)
	{ 
		if (active != NOACTIVE)
		{
			M_Windows[active].Commands.Process(input);
			if (M_Windows[active].callback.key == input)
				M_Windows[active].callback.execute();
		}
	}

}
