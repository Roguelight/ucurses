#include <ucurses/ucurses.hpp>
#include <fstream>

using namespace ucurses;

void test()
{
    std::fstream file("./test", std::ios_base::out);
    file << "Passed" << std::endl;
}

int main()
{
    UCurses gui;
	Window* mainwindow = gui.createWindow();
    mainwindow->addCommand(27, test);

    gui.Run();
    
}

