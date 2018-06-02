#include "CanvasTest.hpp"
        
CanvasTest::CanvasTest() : canvas_data(15, 15)
{
    canvas = new ucurses::Canvas(appwindow);    
    canvas->setColor(5);
    canvas->setPosition(0.5f, 0.5f);
    canvas->setTarget(&canvas_data, ucurses::coord2d(15, 15));
    canvas->alignMiddle();
    for (int x = 0; x < 15; ++x)
        for (int y = 0; y < 15; ++y)
        {
            char a = rg.generateUniform(0, 127);
            canvas_data(x, y) = ((a == 10) ? 0 : a);
        }
}
