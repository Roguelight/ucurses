#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{
    UCurses gui;
	Window* mainwindow = gui.createWindow();

    gui.loadConfig("color_scheme.conf");
    Label* test = new Label(mainwindow);
    test->setSize(20, 0);
    test->setText(std::string(100, '-'));
    test->setPosition(0.5f, 0.5f);
    test->wrapText();
    gui.Run();
    
}
