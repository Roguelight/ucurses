#include <ucurses/gui/Intro.hpp>
	
namespace ucurses { 

	void Intro::Display(Window* win)
	{
		coord2d mid = win->getMiddle();
		win->Clear();

		// Leave it up to the previous UI to set up call backs
		//win->setCallback(KEY_F(3), exit);
		//win->setCallbackTip("F3: Exit Tutorial);

		Label* title = new Label(win, mid.x - 10, 3);
		title->setText("UCurses Introduction");
		
		Label* text = new Label(win, 3, 6);
		text->loadFromFile(".resources/gui/ucurses_welcome");
		text->highlightRow(1, 2, A_BOLD);
		
		win->addCommand(10, std::bind(&Intro::showTitle, win));
	}

	//void Intro::Second(Window* winI
	void Intro::showTips(Window* win)
	{
		coord2d size = win->getSize();
		win->clearCommands();
		
		Label* tipshelp = new Label(win, 3, size.y - 6);
		tipshelp->loadFromFile(".resources/gui/ucurses_command_display");

		win->addTip("n: Advance ");
		win->addCommand('n', std::bind(&Intro::Tab, win));

	}
	
	void Intro::showTitle(Window* win)
	{
		win->clearCommands(); // Clearing commands avoids reconstructing duplicate components
		Label* title = new Label(win, 2, 1);
		title->setText("^ Above this line is the title bar, notice that it is highlighted ^");
		title->appendLine("Press 'c' to continue");
		win->addCommand('c', std::bind(&Intro::showTips, win));
	}

	void Intro::Tab(Window* win)
	{
		win->clearCommands();
		coord2d mid = win->getMiddle();
		Window* extra = win->subWindow(coord2d(60, 10), coord2d(50, 20));
		Label* hidden = new Label(win, 70, 27);
		hidden->setText("Now press 'n' to go to the next window");
		extra->setTitle("Extra window");
		extra->addTip("Enter: Do something");
		extra->addCommand(10, std::bind(&Intro::Extra, extra));
		win->Clear();	
		win->addCommand('n', std::bind(&Intro::Component, win));
		Label* text = new Label(win, 3, 6);
		text->loadFromFile(".resources/gui/tabs_demo");
	}

	void Intro::Extra(Window* win)
	{
		win->clearCommands();
		Label* text = new Label(win, 3, 3);
		text->setText("This window is no longer needed.");
		text->appendLine("Press f2 to destroy this window.");
	}

	void Intro::Component(Window* win)
	{
		win->Clear();
		Menu* menu = new Menu(win, 5, 7);
		Label* menu_display = new Label(win, 5, 18);
		for (int i = 0; i < 10; ++i)
			menu->addItem("Item " + to_string(i));

		Label* menu_help = new Label(win, 5, 3);
		menu_help->loadFromFile(".resources/gui/menu_help");

		TextEntry* entry = new TextEntry(win, 5, 25);
		entry->setSubject("Tutorial entry");

		Label* entry_help = new Label(win, 5, 21);
		entry_help->loadFromFile(".resources/gui/entry_help");
		
		Label* entry_prompt = new Label(win, 5, 27);
		entry_prompt->setText("Enter the string 'Icarus' to finish the tutorial!");

		win->addCommand(10, std::bind(&Intro::Select, win, menu, menu_display));
	}

	void Intro::Select(Window* win, Menu* menu, Label* display)
	{
		display->setText("Selected " + menu->getSelectedItem());
	}

	void Intro::Finish(Window* win, TextEntry* entry)
	{
		if (entry->getText() == "Icarus")
			win->Escape();
	}
}
