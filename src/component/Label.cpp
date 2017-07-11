#include <ucurses/component/Label.hpp>


namespace ucurses { 

    Label::Label(coord x, coord y, Window* host) : Component(x, y, host), text("UCurses Label")
	{
        setSize(30,6);
	}

    void Label::setText(const std::string& inText)
    {
        text = inText;
    }

    void Label::appendText(std::string inText)
    {
        text += inText;
    }

    const std::string& Label::getText() const
    {
        return text;
    }

    void Label::Update()
    {
        setPosition();
        print(text);
    }
}
