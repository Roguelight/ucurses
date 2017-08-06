#include <ucurses/component/Label.hpp>
	#include <ctk/std/vector.hpp>


namespace ucurses { 

    Label::Label(coord x, coord y, Window* host) : Component(x, y, host)
	{

	}

    void Label::Update()
    {
        for (short i = 0; i < text.size(); i++)
        {
			Component::setCursor(0, i);
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
        if (text.size() > cursor)
            text[cursor] = inText;
        else
            text.push_back(inText);
    }
    
	void Label::setText(const std::vector<string>& inText)
	{
		text = inText;
	}
    
	/* 
	* Appends text at line, 
	* if invalid: append to last line 
	*/
    void Label::appendText(const std::string& inText)
    {
        if (text.size() > cursor)
            text[cursor] += inText;
		else
			text[text.size() - 1] += inText;
    }

	void Label::appendLine(const std::string& inText)
	{
		text.push_back(inText);
		++cursor;
	}

    /* Getters */
    const std::string& Label::getText() const
    {
        if (text.size() > cursor)
            return text[cursor];
    }

    const std::string& Label::getTextAt(short linepos) const
    {
        if (text.size() > linepos) 
            return text[linepos];
    }

    void Label::Clear()
    {
        text.clear();
    }

	void Label::loadFromText(const std::string& filename)
	{
		ctk::vector::loadFromFile(text, filename);
	}
}
