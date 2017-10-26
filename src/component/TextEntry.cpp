// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/TextEntry.hpp>
#include <ucurses/window/Window.hpp>

namespace ucurses {

	TextEntry::TextEntry(Window* host, coord x, coord y) : Component(host, x, y)  
	{
		setSize(20, 4);
		input = "";
		subject = "Text";
		//bindDefault();
		onEnter = nullptr;
	}

	void TextEntry::bindDefault()
	{
		addCommand('e', std::bind( &TextEntry::getInput, this));
		addTip("e: Input " + subject);
	}

	void TextEntry::Process(int input)
	{
		if (input == 'e')
			getInput();
	}

	string& TextEntry::getText()
	{
		return input;
	}

	void TextEntry::setText(const std::string& inText)
	{
		input = inText; 
	}

	void TextEntry::Draw()
	{
		print(subject + ": " + input);
	}

	void TextEntry::getInput()
	{
		attributeOn(A_BOLD);
        setCursor();
		Draw();
		coord x = subject.length() + 2;
		echo();
		char in[10];
		setCursor(x, 0);
		//move(-1, 0);
		//
		bool temp = H_Window->isDelay();
		H_Window->setDelay(true);
		wgetnstr(H_Window->getHandle(), in, 12);
		H_Window->setDelay(temp);
		attributeOff(A_BOLD);
		noecho();
		input = in;
		if (onEnter)
			onEnter();
	}

	void TextEntry::setSubject(string inString)
	{
		subject = inString;
	}
			
	void TextEntry::setOnEnter(std::function<void()> func)
	{
		onEnter = func;
	}
}
