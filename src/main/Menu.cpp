#include <ncursespp/application/Application.hpp>
#include <ncursespp/gui/Menu.hpp>

using namespace ncursespp::application;
using namespace ncursespp::gui;

int main(int argc, char* argv[])
{
    Application app;
    app.addWindow("Name Entry", new TextEntry(75,5,"Entity Name"));
    app.Run();
}
