// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/TextEntry.hpp>


namespace ncursespp { namespace gui {

    // 2 rows for text input/output, one top and bottom for border = 4
	TextEntry::TextEntry(coord x, coord y, string subject) : Window(coord2d(40,6), coord2d(x,y)) 
	{
        input = "";
        this->subject = subject;
        setTitle("Text Entry");
        Commands.Add(std::bind( &TextEntry::getInput, this), 'E');
	}

    void TextEntry::Update()
    {
        Window::Update();
        printCommands();
        setPosition(2,2);
        print(subject + ": " + input);
    }

    void TextEntry::getInput()
    {
        coord x = subject.length() + 4;
        echo();
        char in[10];
        setPosition(x, 2);
        print("*");
        move(-1, 0);
        attributeOn(A_STANDOUT);
        wgetnstr(getHandle(), in, 10);
        attributeOff(A_STANDOUT);
        noecho();
        input = in;
    }

    void TextEntry::printCommands()
    {
        Window::printCommands();
        attributeOn(A_REVERSE);
        print("E:");
        attributeOff(A_REVERSE);
        print(" Input ");
    
    }
}}
