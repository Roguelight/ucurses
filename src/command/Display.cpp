#include <ucurses/command/Display.hpp>


namespace ucurses { namespace command {

    Display::Display()
    {
        tips.reserve(8);
    }

    void Display::Add(std::string keyID, std::string funcID)
    {
        tips.push_back(commandmap(keyID, funcID));
    }

    void Display::Clear()
    {
        tips.clear();
    }
}}
