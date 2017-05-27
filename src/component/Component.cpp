// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Component.hpp>
#include <ucurses/gui/Window.hpp>

namespace ucurses { 

	Component::Component(coord x, coord y, Window* host) : H_Window(host)
	{
        position.x = x;
        position.y = y;
	}

    void Component::print(string inString)
    {
        H_Window->print(inString);
    }

    void Component::move(coord x, coord y)
    {
        H_Window->move(x, y);
    }

    void Component::setPosition(coord x, coord y)
    {
        H_Window->setPosition(position.x + x, position.y + y);
    }

    void Component::setPosition()
    {
        H_Window->setPosition(position.x, position.y);
    }

    void Component::addCommand(int key, delegate func)
    {
        H_Window->Commands.Add(key, func);
    }

    void Component::addTip(string keyID, string funcID)
    {
        H_Window->addTip(keyID, funcID);
    }

    coord2d Component::getMiddle() const
    {
        return coord2d(size.x / 2, size.y / 2);
    }

    void Component::attributeOn(int attributes)
    { 
        H_Window->attributeOn(attributes);
    } 

    void Component::attributeOff(int attributes)
    { 
        H_Window->attributeOff(attributes); 
    }

    void Component::setSize(coord x, coord y)
    {
        size.x = x;
        size.y = y;
    }

    coord2d Component::getPosition() const
    {
        return H_Window->getPosition() - position;
    }
            
    // Highlighting
    void Component::highlightWord(coord2d wordpos, int size)
    {
        H_Window->highlightWord(wordpos + position, size);
    }

    void Component::highlightRow(coord row)
    {
        H_Window->highlightRow(row + position.y);
    }

    void Component::highlightColumn(coord column)
    {
        H_Window->highlightColumn(column + position .x);
    }
    
}
