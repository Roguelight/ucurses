#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{

    UCurses gui;
	Window* mainwindow = gui.createWindow();

	Label* item = new Label(mainwindow, 14, 5);
    ScrollableMenu* menu = new ScrollableMenu(mainwindow, 5, 5);
	auto fn = [](Label* item, Menu* menu) { item->setText("Selection " + std::to_string(menu->getSelectedIndex())); };
	menu->setRefresh(std::bind(fn, item, menu));
    for (int i = 0; i < 25; ++i)
    {
        menu->addItem("Item " + std::to_string(i));
    }
	
    gui.Run();	
    
}
