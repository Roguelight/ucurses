#include <ucurses/app/App.hpp>
#include <ucurses/app/GUI.hpp>
#include <ucurses/gui/FileMenu.hpp>
#include <ucurses/gui/TextEntry.hpp>

using namespace ucurses::app;
using namespace ucurses::gui;

int main(int argc, char* argv[])
{
    App app;
    app.addWindow("Name Entry", new TextEntry(75,5,"Entity Name"));
    //app.addWindow("Filemenu 1", new FileMenu(coord2d(60,20), coord2d(5,5)));
    app.Run();
    return 0;

}
