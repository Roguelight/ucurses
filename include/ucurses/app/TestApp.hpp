#pragma once
#include <ucurses/app/Application.hpp>
#include <ctk/random/RandomGenerator.hpp>

class TestApp : public ucurses::Application
{
    public:

    TestApp();

    virtual void Update();

    protected:

    ucurses::Label* text;
    
};

