// Copyright Fri Mar 10 17:16:30 2017
// Liam Rogers, All rights reserved.

#include "TestWindow.hpp"
#include <ncursespp/gui/Menu.hpp>
#include <ncursespp/gui/TextEntry.hpp>


namespace ncursespp { namespace gui {

	TestWindow::TestWindow() : Window(coord2d(70, 30), coord2d(3, 3), 2)
	{
        Menu* menu = new Menu(4,4,this);
        menu->addItem("New Game");
        menu->addItem("Load Game");
        menu->addItem("Options");
        menu->bindDefault();
        Components.Add(menu);

        TextEntry* entry = new TextEntry(40,4,this);
        entry->bindDefault();
        Components.Add(entry);
        setTitle("Test Window");
	}

}}
