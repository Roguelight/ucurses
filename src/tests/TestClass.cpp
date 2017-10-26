#include <ucurses/tests/TestClass.hpp>


namespace ucurses { 

	TestClass::TestClass()
	{

	}

	void TestClass::Run()
	{
		Window* main = gui.createWindow(); // Create Full-screen window
		ucurses::mainScreen(main);
		gui.Run();	
	}

	void mainScreen(Window* target)
	{
		target->Clear();

		short x = target->getMiddle().x - 10;

		Label* Title = new Label(target, x, 10);
		Title->setText("Zombie Dogs and Lava Frogs");

		Menu* H_ModeSelect = new Menu(target, x, 20);
		H_ModeSelect->addItem("New Game");
		H_ModeSelect->addItem("Load Game");
	}
}
