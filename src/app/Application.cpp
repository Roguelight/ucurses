#include <ucurses/app/Application.hpp>

namespace ucurses {
    
    Application::Application()
    {
        appwindow = gui.createWindow();
        appwindow->setDelay(false);
    }

    void Application::processInput()
    {
        gui.handleInput();
    }

    void Application::Render()
    {
        if (gui.Running())
            gui.Render(); 
        else
            Quit();
    }

    void Application::setName(const std::string& inName)
    {
        name = inName;
        appwindow->setTitle(inName);
    }
}
