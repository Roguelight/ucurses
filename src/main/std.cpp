#include <ncursespp/application/Application.hpp>
#include <ncursespp/gui/Window.hpp>

using namespace ncursespp::application;
using namespace ncursespp::gui;

int main(int argc, char* argv[])
{
    Application app;
    app.getGUI()->addWindow("stdscr", new Window);
    app.getGUI()->getWindow("stdscr")->print("This is an object oriented stdscr");
    app.Run();

}
