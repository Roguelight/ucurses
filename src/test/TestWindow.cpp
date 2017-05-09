#include <ucurses/app/App.hpp>
#include <ucurses/tests/TestWindow.hpp>

using namespace ucurses::tests;
using namespace ucurses::app;

int main(int argc, char* argv[])
{
    App app;
    app.addWindow("Window One", new TestWindow(coord2d(1,1)));
    app.addWindow("Window Two", new TestWindow(coord2d(20,1)));
    app.Run();

}
