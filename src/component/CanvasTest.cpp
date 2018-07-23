#include "CanvasTest.hpp"

using namespace ucurses;

CanvasTest::CanvasTest()
{
    canvas = new Canvas(appwindow, coord2d(15, 15));    
    canvas->setColor(5);
    canvas->setPosition(0.5f, 0.5f);
    //canvas->setTarget(&canvas_data, ucurses::coord2d(15, 15));
    canvas->alignMiddle();
}
