#include <ucurses/gui/FileNav.hpp>


namespace ucurses { namespace gui {

    FileNav::FileNav(coord x, coord y, Window* host) : FileMenu(x, y , host)
	{

	}

    void FileNav::Select()
    {
        if (selection != NONE)
        {
            string dir(directory + "/" + items.at(selection));
            if (boost::filesystem::is_directory(dir))
            {
                last = directory;
                setDirectory(dir);
            }
            else
                GlobalLogger::log(WARNING, "Filemenu:") << "Selected file is not a directory" << dir << Sentinel::END;
        }
        else
            GlobalLogger::log(ERROR, "Filemenu:") << "Please make a valid selection!" << Sentinel::END;
    }
        
    void FileNav::bindDefault()
    { 
        //addCommand('b', bind( &FileMenu::backTrack, this)); 
        //addCommand('p', bind( &FileMenu::toParent, this));
            
    }

}}
