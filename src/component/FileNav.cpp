#include <ucurses/component/FileNav.hpp>

namespace ucurses { 

	FileNav::FileNav(coord x, coord y, Window* host) : FileMenu(x, y , host)
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
