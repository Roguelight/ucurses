// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

#include "FileMenu.hpp"
#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace gui {

	FileMenu::FileMenu() : directory("./")
	{
        refreshList();
	}
            
    FileMenu::FileMenu(coord2d size, coord2d position) : Menu(size, position)
    {
        directory = "./";
        refreshList();
    }

    void FileMenu::refreshList()
    {
        GlobalLogger::log(TRACE) << "Refreshing list for directory" << directory <<  Sentinel::END;
        ctk::file::Directory dir(directory);
        std::vector<string> files;
        dir.copyContents(files);
        for (auto& file : files)
            addItem(file);
    }

    void FileMenu::Update()
    {
        setAttribute(S_Colors->Get("Default"));
        Menu::Update();
    }

}}
