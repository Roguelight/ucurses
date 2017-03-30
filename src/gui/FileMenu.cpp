// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/FileMenu.hpp>

namespace ncursespp { namespace gui {

            
    FileMenu::FileMenu(coord x, coord y, Window* host) : Menu(x, y, host)
    {
        GlobalLogger::log(TRACE, "Filemenu::") << "Initialising FileMenu" <<  Sentinel::END;
        setDirectory(boost::filesystem::current_path().string());
        last = directory;
    }

    void FileMenu::Update()
    {
        Menu::Update();
        printCommands();
    }

    void FileMenu::bindDefault()
    {
        Menu::bindDefault();
        addCommand('b', bind( &FileMenu::backTrack, this)); 
        // addCommand('p', bind( &FileMenu::toParent, this)); Not desirable for most filemenus
        
    }

    void FileMenu::printCommands()
    {
        Menu::printCommands();
        attributeOn(A_REVERSE);
        print("j:");
        attributeOff(A_REVERSE);
        print(" Down ");
        attributeOn(A_REVERSE);
        print("k:");
        attributeOff(A_REVERSE);
        print(" Up ");
    }

    void FileMenu::setDirectory(string inString)
    {
        GlobalLogger::log(TRACE, "Filemenu:") << "Setting directory to: " << inString <<  Sentinel::END;
        last = directory;
        directory = inString;
        ctk::file::Directory dir(directory);
        dir.copyContents(items);

        if (!(items.empty()))
            selection = 0;
        else
            selection = -1;
    }

    void FileMenu::Select()
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

    void FileMenu::toParent()
    {
        boost::filesystem::path dir(directory);
        string parentpath(dir.parent_path().string());
        GlobalLogger::log(TRACE) << "Backtracking to directory: " << parentpath <<  Sentinel::END;
        setDirectory(parentpath);
        selection = 0;
    }

    void FileMenu::backTrack()
    {
        string temp = directory;
        setDirectory(last);
        last = temp;
    }


}}
