// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/Window.hpp>
#include <ucurses/window/Interface.hpp>
#include <ucurses/app/UCurses.hpp>

namespace ucurses {

	UCurses* Window::ucurses = nullptr;
	ColorContainer* Window::colors = nullptr;

	Window::Window(coord2d size, coord2d position) : color(0), interface(nullptr)
	{
		H_Window = newwin(size.y, size.x, position.y, position.x);
		keypad(H_Window, TRUE);
		deletable = false;
		setDelay(true);
		setDefaultColor(1);
	}

	Window::Window() : color(0), interface(nullptr)
	{
		H_Window = newwin(0,0,0,0);
		keypad(H_Window, TRUE);
		deletable = false;
		setDelay(true);
		setDefaultColor(1);
	}

	Window::~Window()
	{
		delete interface;
		delwin(H_Window);
	}

	Window* Window::subWindow(coord2d size, coord2d pos)
	{
		return ucurses->createWindow(size, pos);
	}

	void Window::printCommands()
	{
		coord2d size = getSize();
		setCursor(2, size.y - 2);
		for (auto& tip : tips)
		{
			print(tip);
			print("  ");
		}
		setCursor(size.x - (callback_stack.getTip().size() + 2), getSize().y - 2);

		print(callback_stack.getTip());

		if (ucurses->showHelp())
		{
			setCursor(2, 2);
			for (auto& tip : ucurses->getTips())
			{
				print(tip);
				print("  ");
			}
		}
	}

	void Window::Clear()
	{
		Commands.Clear();
		tips.clear();
		Components.RemoveAll();
	}

	void Window::clearCommands()
	{
		Commands.Clear();
		tips.clear();
	}

	void Window::clearComponents()
	{
		Components.RemoveAll();
	}

	void Window::addComponent(Component* component)
	{
		Components.Add(component);
	}

	void Window::addCommand(int key, delegate func)
	{
		Commands.Add(key,func);
	}

	void Window::Escape()
	{
		callback_stack.Execute(); 
	}

	void Window::pushCallback(int key, delegate func)
	{
		callback_stack.Emplace(key, func);
	}

	void Window::setCallbackTip(const string& in)
	{ 
		callback_stack.setTip(in); 
	}

	void Window::addTip(const std::string& tip)
	{
		tips.push_back(tip);
	}

	void Window::addTip(string&& tip)
	{
		tips.push_back(tip);
	}

	/* Update */

	void Window::Update()
	{
		printBorder();
		setCursor(2,0);
		print(title);
		printCommands();
		Components.Update();
	}

	void Window::ClearScreen()
	{
		werase(H_Window);
	}

	void Window::printBorder()
	{
		box(H_Window, '|', '-');
	}

	/* Construction */

	void Window::EnableColor(ColorContainer* s_ptr) 
	{
		colors = s_ptr;
	}

	void Window::setTitle(const std::string& s)
	{
		title = s;        
	}

	void Window::setDelay(bool b)
	{
		delay = b;
		nodelay(H_Window, !b);
	}

	bool Window::isDelay() const
	{
		return delay;
	}

	void Window::setDelete(bool b)
	{
		deletable = b;
	}

	/* Manipulation */

	void Window::moveCursor(coord x, coord y)
	{ 
		coord2d curpos = getCursor();
		wmove(H_Window, curpos.y + y, curpos.x + x);
	}

	void Window::print(const std::string& inString)
	{
		waddstr(H_Window, inString.c_str());
	}

	void Window::print(char c)
	{
		waddch(H_Window, c);
	}

	void Window::print(char* c)
	{
		waddstr(H_Window, c);
	}

	void Window::setCursor(coord x, coord y)
	{
		wmove(H_Window, y, x);
	}

	// Attributes        

	void Window::setAttributes(int attributes)      
	{
		wattrset(H_Window, attributes); 
	}

	void Window::attributeOn(int attributes)
	{ 
		wattron(H_Window, attributes);  
	} 

	void Window::attributeOff(int attributes)
	{ 
		wattroff(H_Window, attributes); 
	}

	void Window::setDefaultColor(short color)
	{
		this->color = color;
		wattron(H_Window, COLOR_PAIR(this->color));	
		wbkgdset(H_Window, COLOR_PAIR(color));
	}

	void Window::setColor(short color)
	{
		wattron(H_Window, COLOR_PAIR(color));	
	}

	short Window::getColor()
	{
		return color;
	}

	void Window::unsetColor(short color)
	{
		wattroff(H_Window, COLOR_PAIR(color));	
		wattron(H_Window, COLOR_PAIR(this->color));	
	}

	// Highlighting

	void Window::highlightRow(coord row, short color, attr_t attributes)
	{
		mvwchgat(H_Window, row, 0, -1, attributes, color, NULL);
	}

	void Window::highlightColumn(coord column, short color, attr_t attributes)
	{
		mvwchgat(H_Window, 0, column, -1, attributes, color, NULL);
	}    

	void Window::highlightWord(coord2d wordpos, int size, short color, attr_t attributes)
	{
		mvwchgat(H_Window, wordpos.y, wordpos.x, size, attributes, color, NULL);
	}

	void Window::highlightChar(coord2d wordpos, short color, attr_t attributes)
	{
		highlightWord(wordpos, 1, color, attributes);
	}

	/* Retrieval methods */

	coord2d Window::getSize() const
	{
		coord2d size;
		getmaxyx(H_Window, size.y, size.x);
		return size;
	}

	coord2d Window::getMiddle() const
	{
		coord2d size = getSize(); 
		coord2d middle(size.x / 2, size.y / 2);
		return middle;
	}

	coord2d Window::getCursor() const
	{
		coord2d pos;
		getyx(H_Window, pos.y, pos.x);
		return pos;
	}

	coord2d Window::getPosition() const
	{
		coord2d pos;
		getbegyx(H_Window, pos.y, pos.x);
		return pos;
	}

	void Window::setPosition(coord x, coord y)
	{
		mvwin(H_Window, y, x);
	}

}
