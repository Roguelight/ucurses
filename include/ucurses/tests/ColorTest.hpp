#pragma once
#include <ucurses/app/Application.hpp>

#define COLOR1
class ColorText : public ucurses::Application
{
    public:

    ColorTest();

    virtual void Update();

    protected:

    ucurses::Label* text;
    
};
