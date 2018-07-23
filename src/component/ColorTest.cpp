#include "ColorTest.hpp"

using namespace ucurses;


        
ColorTest::ColorTest()
{
    some_text = new ucurses::Label(appwindow);
    colored_text = new ucurses::Label(appwindow);
    some_text->setText("Default text widget");
    colored_text->setText("Colored text widget");

    some_text->setPosition(0.2f, 0.2f);
    colored_text->setPosition(some_text->getPosition());
    colored_text->getPosition().y += 1;

    canvas = new ucurses::Canvas(appwindow, coord2d(15, 15));
    canvas->setPosition(0.1f, 0.1f);
    appwindow->Commands.Add('f', [=] ()
    {
        Cell* cell = canvas->cells.Get(1, 1);
        cell->symbol = 'x';
        cell->color++;
    });
}
        
void ColorTest::Update()
{
    
}
