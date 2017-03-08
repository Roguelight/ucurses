// Copyright Wed Mar  8 02:49:05 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/TextEntry.hpp>


namespace ncursespp { namespace gui {

	TextEntry::TextEntry(coord2d size, coord2d pos)
	{
        setTitle("Text Entry");
	}


    void TextEntry::Update()
    {
        Window::Update();

        move(coord2d(4,2));
        print("Enter " + title);
        move(coord2d(4,3));
        echo();
        char input[10];
        getnstr(input, 10);
        noecho();
        if (input)
        {
            string temp(input);
            move(coord2d(4,4));
            print("You entered: " + temp);
        }
    
    }

}}
