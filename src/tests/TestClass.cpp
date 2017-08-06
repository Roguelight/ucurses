#include <ucurses/tests/TestClass.hpp>


namespace ucurses { 

	TestClass::TestClass()
	{

	}

	void TestClass::Run()
	{
		Window* main = gui.createWindow(); // Create Full-screen window
		ucurses::mainScreen(main);
		//main->setDelay
		gui.Start();

		while( gui.Okay() )
		{
			int key = gui.getInput();
			gui.Clear();
			gui.handleInput(key);
			gui.Render();
		}
	}

	void mainScreen(Window* target)
	{
		target->Clear();

		short x = target->getMiddle().x - 10;

		Label* Title = new Label(x, 10, target);
		Title->setText("Zombie Dogs and Lava Frogs");

		Menu* H_ModeSelect = new Menu(x, 20, target);
		H_ModeSelect->addItem("New Game");
		H_ModeSelect->addItem("Load Game");
	}
}
