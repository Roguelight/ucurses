#include <ucurses/component/Label.hpp>


namespace ucurses { 

    Label::Label(coord x, coord y, Window* host) : Component(x, y, host)
	{
        setSize(30,6);
	}

    void Label::Update()
    {
        setPosition();
        for (short i = 0; i < text.size(); i++)
        {
            setPosition(0, i);
            print(text[i]);
        }
    }
    
    /* Safe sets ;) */
    void Label::setText(const std::string& inText)
    {
        if (!text.empty())
            text[FIRST] = inText;
        else
            text.push_back(inText);
    }
    
    void Label::setTextAt(const std::string& inText, short linepos)
    {
        if (text.size() > linepos) 
            text[linepos] = inText;
    }
    
    /* Safe Appendage */
    void Label::appendText(const std::string& inText)
    {
        if (!text.empty())
            text[FIRST] += inText;
    }

    void Label::appendTextAt(const std::string& inText, short linepos)
    {
        if (text.size() > linepos) 
            text[linepos] += inText;
    }

    void Label::appendLine(const std::string& inText)
    {
        text.push_back(inText);
    }

    /* Getters */
    const std::string& Label::getText() const
    {
        if (!text.empty())
            return text[FIRST];
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
}
