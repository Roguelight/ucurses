#include <ucurses/app/App.hpp>
#include <ucurses/gui/Window.hpp>

using namespace ucurses::app;
using namespace ucurses::gui;

int main(int argc, char* argv[])
{
    App app;
    app.getGUI()->addWindow("stdscr", new Window);
    app.getGUI()->getWindow("stdscr")->print("This is an object oriented stdscr");
    app.Run();

}
