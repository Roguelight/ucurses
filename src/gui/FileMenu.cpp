// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

#include "FileMenu.hpp"
#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace gui {

            
    FileMenu::FileMenu(coord2d size, coord2d position) : Menu(size, position)
    {
        GlobalLogger::log(TRACE, "Filemenu::") << "Initialising FileMenu" <<  Sentinel::END;
        setTitle("Filemenu");
        setDirectory(boost::filesystem::current_path().string());
        last = directory;
        addCommands();
    }

    void FileMenu::Update()
    {
        Menu::Update();
        printCommands();
    }

    void FileMenu::addCommands()
    {
        Commands.Add(bind( &FileMenu::backTrack, this), 'b'); 
        Commands.Add(bind( &FileMenu::toParent, this), 'p'); 
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
        attributeOn(A_REVERSE);
        print("p:");
        attributeOff(A_REVERSE);
        print(" To parent ");
        attributeOn(A_REVERSE);
        print("b:");
        attributeOff(A_REVERSE);
        print(" Back ");
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
