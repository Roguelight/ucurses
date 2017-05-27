// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/FileMenu.hpp>
using namespace ctk::log;
namespace ucurses { 
            
    FileMenu::FileMenu(coord x, coord y, Window* host) : Menu(x, y, host)
    {
        setDirectory(boost::filesystem::current_path().string());
        last = directory;
    }

    void FileMenu::setDirectory(string inString)
    {
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
        setDirectory(parentpath);
        selection = 0;
    }

    void FileMenu::backTrack()
    {
        string temp = directory;
        setDirectory(last);
        last = temp;
    }
}
