// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/Component.hpp>

namespace ucurses { 

	Component::Component(coord x, coord y, Window* host) : H_Window(host)
	{
		highlightColor = 1;
		color = 0;
		position.x = x;
		position.y = y;
		H_Window->addComponent(this);
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

	void Component::moveCursor(coord x, coord y)
	{
		H_Window->moveCursor(x, y);
	}

	void Component::setCursor(coord x, coord y)
	{
		H_Window->setCursor(position.x + x, position.y + y);
	}

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

	void Component::setSize(coord2d size)
	{
		this->size = size;
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
}
