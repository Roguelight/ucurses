#include <ucurses/app/App.hpp>
#include <ucurses/gui/TextEntry.hpp>

using namespace ucurses::app;
using namespace ucurses::gui;

int main(int argc, char* argv[])
{
    App app;
    app.addWindow("Entity Name", new TextEntry(coord2d(50,20), coord2d(5,5)));
    //app.getGUI()->addWindow("Filemenu 1", new FileMenu);
    app.Run();
    return 0;

}
