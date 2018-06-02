#include <ucurses/app/Application.hpp>

namespace ucurses {
    
    Application::Application()
    {
        appwindow = gui.createWindow();
        appwindow->setDelay(false);
        gui.Start();
    }

    void Application::processInput()
    {
        gui.handleInput();
    }

    void Application::Render()
    {
        running = gui.Running();
        gui.Render(); 
    }

    void Application::setName(const std::string& inName)
    {
        name = inName;
        appwindow->setTitle(inName);
    }
}
