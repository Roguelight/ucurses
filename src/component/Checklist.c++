#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{
    UCurses gui;
	Window* mainwindow = gui.createWindow();

    Checklist* checklist = new Checklist(mainwindow, 10, 10);

    for (int i = 0; i < 10; ++i)
        checklist->addItem("Item " + std::to_string(i));

	gui.Run(); 
}
