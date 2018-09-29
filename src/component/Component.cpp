// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Component.hpp>
#include <ucurses/window/Window.hpp>
#include <ucurses/window/Interface.hpp>

namespace ucurses { 

	Component::Component(Window* host, coord x, coord y) : H_Window(host), position(x, y), active(true)
	{
		highlightColor = 2;
		color = H_Window->getColor();
		H_Window->Components.Add(this);
	}
	
	Component::Component(Window* host, coord2d pos) : H_Window(host), position(pos), active(true)
	{
		highlightColor = 2;
		color = H_Window->getColor();
		H_Window->Components.Add(this);
	}

	Component::Component(Interface* host, coord2d pos) : H_Window(host->getTarget()), active(true)
	{

	}

	void Component::Update()
	{
        // Sets window draw position to component position
		setCursor();

        // Sets window draw color to component color
		wcolor_set(H_Window->getHandle(), color, nullptr);

        if (visible)
		    Draw();

		H_Window->resetColor(); 	                            
	}

	void Component::print(const std::string& inString)
	{
		H_Window->print(inString);
	}

	void Component::print(char c)
	{
		H_Window->print(c);
	}

	void Component::print(char* c)
	{
		H_Window->print(c);
	}
	
    void Component::print(Cell* cell)
	{
		H_Window->print(*cell);
	}

	void Component::moveCursor(coord x, coord y)
	{
		H_Window->moveCursor(x, y);
	}

	// Sets position relative of components
	void Component::setCursor(coord x, coord y)
	{
		H_Window->setCursor(position.x + x, position.y + y);
	}

	// Sets cursor to component position
	void Component::setCursor()
	{
		H_Window->setCursor(position.x, position.y);
	}

	void Component::addCommand(int key, delegate func)
	{
		H_Window->Commands.Add(key, func);
	}

	void Component::addTip(string& tip) 
	{
		H_Window->addTip(tip);
	}

	void Component::addTip(string&& tip)
	{
		H_Window->addTip(tip);
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

	coord2d Component::getSize()
	{
		return size;
	}

	void Component::setSize(coord2d size)
	{
		this->size = size;
	}

	void Component::setPosition(short x, short y)
	{
		position.x = x;
		position.y = y;
	}
		
	// Relative positioning
	void Component::move(coord x, coord y)
	{
		position.x += x;
		position.y += y;
	}
	
	void Component::setPosition(float x, float y)
	{
		short xpos = H_Window->getSize().x * x;
		short ypos = H_Window->getSize().y * y;

		// Approximate position of components centre
		ypos -+ (size.y / 2);
		xpos -+ (size.x / 2);

		position.x = xpos;
		position.y = ypos;
	}
			
    void Component::setPosition(coord2d& src)
    {
        position = src;
    }
            
    coord2d& Component::getPosition()
    {
        return position;
    }

	coord2d Component::getPosition() const
	{
		return position;
	}

	coord2d Component::getCursor() const
	{
		return H_Window->getCursor() - position;
	}

	/* Highlighting */

	void Component::highlightWord(coord2d wordpos, int size, short color, attr_t attributes)
	{
		H_Window->highlightWord(wordpos + position, size, color, attributes);
	}

	void Component::highlightRow(coord row, short color, attr_t attributes)
	{
		H_Window->highlightWord(coord2d(position.x, row + position.y), size.x, color, attributes);
	}

	void Component::highlightColumn(coord column, short color, attr_t attributes)
	{
		H_Window->highlightColumn(column + position .x, color, attributes);
	}

	void Component::highlightChar(coord2d pos, short color, attr_t attributes)
	{
		highlightWord(pos, 1, color, attributes);
	}

	void Component::setHighlight(short color)
	{
		highlightColor = color;
	}

	void Component::setColor(short color)
	{
		this->color = color;
	}

    void Component::setActive(bool b)
    {
        active = b; 
    }

    void Component::toggleActive()
    {
        active = !active;
    }
    
    bool Component::isActive()
    {
        return active;
    }
            
    void Component::setVisibility(bool b)
    {
        visible = b; 
    }

    void Component::toggleInvisibility()
    {
        visible = !visible;
    }

    bool Component::isVisible()
    {
        return visible;    
    }

    void Component::_process(int input)
    {
        if (active)
            Process(input);
    }
    
    void Component::alignMiddle()
    {
        position.x -= size.x / 2;
    }
}
