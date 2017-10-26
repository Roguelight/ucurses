#include <ucurses/component/FileNav.hpp>

namespace ucurses { 

	FileNav::FileNav(Window* host, coord x, coord y) : FileMenu(host, x, y)
	{

	}

	void FileNav::Select()
	{
		if (selection != NOSELECT)
		{
			string dir(directory + "/" + items.at(selection));
			if (boost::filesystem::is_directory(dir))
			{
				last = directory;
				setDirectory(dir);
			}
		}
	}

	void FileNav::bindDefault()
	{ 
		//addCommand('b', bind( &FileMenu::backTrack, this)); 
		//addCommand('p', bind( &FileMenu::toParent, this));
	}

}
