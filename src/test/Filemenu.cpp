#include <ncursespp/application/Application.hpp>
#include <ncursespp/gui/FileMenu.hpp>

using namespace ncursespp::application;
using namespace ncursespp::gui;

int main(int argc, char* argv[])
{
    Application app;
    app.addWindow("Filemenu 1", new FileMenu(coord2d(50,20), coord2d(5,5)));
    //app.getGUI()->addWindow("Filemenu 1", new FileMenu);
    app.Run();
    return 0;

}
