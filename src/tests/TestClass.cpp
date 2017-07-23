#include <ucurses/tests/TestClass.hpp>


namespace ucurses { 

	TestClass::TestClass()
	{

	}

    void TestClass::Run()
    {
        Window::Ptr main = gui.createWindow();
        ucurses::mainScreen(gui.getActiveWindow());

        gui.Run();
    }

    void mainScreen(Window* target)
    {
        target->Clear();
        target->addTip("F1: Quit");
        
        short x = target->getMiddle().x - 10;

        Label* Title = new Label(x, 10, target);
        Title->setText("Zombie Dogs and Lava Frogs");
        target->addComponent(Title);

        Menu* H_ModeSelect = new Menu(x, 20, target);
        H_ModeSelect->addItem("New Game");
        H_ModeSelect->addItem("Load Game");
        H_ModeSelect->bindDefault();
        target->addComponent(H_ModeSelect);
    }
}
