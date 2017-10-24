#include <ucurses/ucurses.hpp.hpp>

using namespace ucurses;

int main()
{

    UCurses gui;
	Window* mainwindow = gui.createWindow();

    ScrollableMenu* menu = new ScrollableMenu(mainwindow, 5, 5);
    for (int i = 5; i < 35; ++i)
    {
        menu->addItem("Item " + std::to_string(i));
    }
	
    gui.Run();	
    
}
