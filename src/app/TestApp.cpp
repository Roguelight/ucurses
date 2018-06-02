#include <ucurses/app/TestApp.hpp>

using namespace ucurses;
using namespace std::chrono;
TestApp::TestApp()
{
    text = new Label(appwindow);
    text->setPosition(0.2f, 0.2f);
    appwindow->setDelay(false);
    setName("Real-time application");
}

// Add time functionality to base ctk::Application
void TestApp::Update()
{
    text->setText(std::to_string(duration_cast<milliseconds>(getElapsedTime()).count()));
}
