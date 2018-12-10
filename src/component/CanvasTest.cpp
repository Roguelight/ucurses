#include "CanvasTest.hpp"

using namespace ucurses;

CanvasTest::CanvasTest()
{
    init_pair(5, COLOR_RED, COLOR_BLUE);
    init_pair(4, COLOR_GREEN, COLOR_BLUE);
    canvas = new Canvas(appwindow, coord2d(15, 15));    
    canvas->setColor(5);
    canvas->cells.Get(0,0)->color = 5;
    canvas->cells.Get(1,0)->color = 4;
    canvas->cells.Get(2,0)->color = 1;
    std::fstream file("colortest", std::ios_base::out);
    file << canvas->cells.Get(3,0)->color;
    file.close();
    canvas->setPosition(0.5f, 0.5f);
    //canvas->setTarget(&canvas_data, ucurses::coord2d(15, 15));
    canvas->alignMiddle();
}
