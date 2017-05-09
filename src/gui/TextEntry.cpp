// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

#include <ucurses/gui/TextEntry.hpp>
#include <ucurses/gui/Window.hpp>

namespace ucurses { namespace gui {

    // 2 rows for text input/output, one top and bottom for border = 4
	TextEntry::TextEntry(coord x, coord y, Window* host) : Component(x, y, host)  
	{
        setSize(20, 4);
        input = "";
        subject = "Enter Text";
	}

    void TextEntry::bindDefault()
    {
        addCommand('E', std::bind( &TextEntry::getInput, this));
    }

    void TextEntry::Update()
    {
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
        wgetnstr(H_Window->getHandle(), in, 10);
        attributeOff(A_STANDOUT);
        noecho();
        input = in;
    }

    void TextEntry::printCommands()
    {
        printPosition();
        attributeOn(A_REVERSE);
        print("E:");
        attributeOff(A_REVERSE);
        print(" Input ");
    }

    void TextEntry::setSubject(string inString)
    {
        subject = inString;
    }
}}
