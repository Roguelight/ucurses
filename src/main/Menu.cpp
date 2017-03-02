#include <ncursespp/application/Application.hpp>
#include <ncursespp/gui/Menu.hpp>

using namespace ncursespp::application;
using namespace ncursespp::gui;

int main(int argc, char* argv[])
{
    Application app;
    app.getGUI()->addWindow("Menu 1", new Menu);
    app.Run();
}
