// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Component.hpp>


namespace ncursespp { namespace gui {

	Component::Component(coord x, coord y, Window* host) : H_Window(host)
	{
        GlobalLogger::log(TRACE,"NCursespp::Component") << "Constructing component" << Sentinel::END;
	}

    void Component::print(string inString)
    {
        H_Window->print(inString);
    }

    void Component::move(coord x, coord y)
    {
        H_Window->move(x, y);
    }

    void Component::setPostion(coord x, coord y)
    {
        H_Window->setPosition(x, y);
    }

    void Component::addCommand(int key, delegate func)
    {
        H_Window->Commands.Add(func, key);
    }

    void Component::getMiddle() const
    {
        return coord2d(size.x / 2, size.y / 2);
    }

    void Component::commandPrintPos()
    {
        setPosition(0, (pos.y + size.y) - 2);
    }
    
    void Component::attributeOn(int attributes)
    { 
        H_Window->attributeOn(attributes);
    } 

    void Component::attributeOff(int attributes)
    { 
        H_Window->attributeOn(attributes); 
    }

    void Component::setSize(coord x, coord y)
    {
        size.x = x;
        size.y = y;
    }

    
}}
