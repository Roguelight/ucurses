#include <ncursespp/application/Application.hpp>
#include <ncursespp/application/GUI.hpp>
#include <ncursespp/gui/FileMenu.hpp>
#include <ncursespp/gui/TextEntry.hpp>

using namespace ncursespp::application;
using namespace ncursespp::gui;

int main(int argc, char* argv[])
{
    Application app;
    //app.addWindow("Name Entry", new TextEntry(75,5,"Entity Name"));
    //app.addWindow("Filemenu 1", new FileMenu(coord2d(60,20), coord2d(5,5)));
    app.Run();
    return 0;

}
