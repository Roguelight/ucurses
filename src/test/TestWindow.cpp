#include <ncursespp/application/Application.hpp>
#include <ncursespp/gui/TestWindow.hpp>

using namespace ncursespp::gui;
using namespace ncursespp::application;

int main(int argc, char* argv[])
{
    Application app;
    app.addWindow("Test Window", new TestWindow());
    app.Run();

}
