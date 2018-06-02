#include <ucurses/component/Label.hpp>
#include <ctk/std/string.hpp>
#include <algorithm>

namespace ucurses { 

	Label::Label(Window* host, coord x, coord y) : Component(host, x, y)
	{
        size.x = 50;
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
        size.x = inText.length() / 2;
	}

    void Label::wrapText()
    {
        int frac = text.length() / size.x;
        if (frac > 0)
            for (int i = 1; i <= frac; ++i)
                text[i * size.x] = '\n';
    }
            
    void Label::alignMiddle()
    {
        position.x -= text.length() / 2;
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
	
	std::string& Label::getText() 
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
