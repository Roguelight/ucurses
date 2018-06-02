#pragma once
#include <ucurses/ucurses.hpp>

class CanvasTest : public ucurses::Application
{
    public:   
        
        CanvasTest();

    protected:

        ArrayXc canvas_data;
        ctk::RandomGenerator rg;
        ucurses::Canvas* canvas;
};
