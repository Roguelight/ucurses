// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/FileMenu.hpp>

namespace ucurses { namespace gui {

            
    FileMenu::FileMenu(coord x, coord y, Window* host) : Menu(x, y, host)
    {
        GlobalLogger::log(TRACE, "Filemenu::") << "Initialising FileMenu" <<  Sentinel::END;
        setDirectory(boost::filesystem::current_path().string());
        last = directory;
    }

    void FileMenu::Update()
    {
        Menu::Update();
    }

    void FileMenu::bindDefault()
    {
        Menu::bindDefault();
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
