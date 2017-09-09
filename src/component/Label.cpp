#include <ucurses/component/Label.hpp>
#include <ctk/std/string.hpp>

namespace ucurses { 

	Label::Label(coord x, coord y, Window* host) : Component(x, y, host)
	{

	}

	void Label::Draw()
	{
		for (short i = 0; i < text.size(); i++)
		{
			if (text[i] == '\n')
				Component::setCursor(0, getCursor().y + 1);
			else
				print(text[i]);
		}
	}

	/* Safe sets ;) */

	/* 
	 * Sets text at line, 
	 * if invalid: create new line at end 
	 */
	void Label::setText(const std::string& inText)
	{
		text = inText;
	}

	/* 
	 * Appends text at line, 
	 * if invalid: append to last line 
	 */
	void Label::appendText(const std::string& inText)
	{
		text.append(inText);
	}

	void Label::appendLine(const std::string& inText)
	{
		text.append('\n' + inText);
	}

	/* Getters */
	const std::string& Label::getText() const
	{
		return text;
	}

	void Label::Clear()
	{
		text.clear();
	}

	void Label::loadFromFile(const std::string& filename)
	{
		ctk::string::loadFromFile(text, filename);
	}
}
