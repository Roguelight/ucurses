#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{
    UCurses gui;
	Window* mainwindow = gui.createWindow();

	Interface* combat_menu = new CombatMenu();

    gui.loadConfig("color_scheme.conf");
    combat_menu->Bind(mainwindow);
    gui.Run(); 
}
