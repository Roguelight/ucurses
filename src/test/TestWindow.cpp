#include <ncursespp/application/Application.hpp>
#include <ncursespp/tests/TestWindow.hpp>

using namespace ncursespp::tests;
using namespace ncursespp::application;

int main(int argc, char* argv[])
{
    Application app;
    app.addWindow("Window One", new TestWindow(coord2d(1,1)));
    app.addWindow("Window Two", new TestWindow(coord2d(20,1)));
    app.Run();

}
