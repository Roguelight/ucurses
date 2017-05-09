#include <ucurses/app/app.hpp>
#include <ucurses/gui/Menu.hpp>

using namespace ucurses::app;
using namespace ucurses::gui;

int main(int argc, char* argv[])
{
    App app;
    app.addWindow("Name Entry", new TextEntry(75,5,"Entity Name"));
    app.Run();
}
