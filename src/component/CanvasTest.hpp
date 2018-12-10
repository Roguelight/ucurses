#pragma once
#include <ucurses/ucurses.hpp>



class CanvasTest : public ucurses::Application
{
    public:   

        CanvasTest();

    protected:

        ctk::RandomGenerator rg;
        ucurses::Canvas* canvas;
};

