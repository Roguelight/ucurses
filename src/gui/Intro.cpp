#include <ucurses/gui/Intro.hpp>
	
namespace ucurses { 

	void Intro::Display(Window* win, std::function<void()> const& exit)
	{
		coord2d mid = win->getMiddle();
		win->Clear();
		win->setCallback(KEY_F(3), exit);
		win->setCallbackTip("F3: Exit Tutorial");

		Label* title = new Label(mid.x - 10, 3, win);
		title->setText("UCurses Introduction");
		
		Label* text = new Label(3, 6, win);
		text->loadFromFile(".resources/gui/ucurses_welcome");
		
		win->addCommand(10, std::bind(&Intro::showTitle, win));
		
		win->addComponent(title);
		win->addComponent(text);
	
	}

	//void Intro::Second(Window* winI
	void Intro::showTips(Window* win)
	{
		coord2d size = win->getSize();
		win->clearCommands();
		Label* tipshelp = new Label(3, size.y - 6, win);
		win->addComponent(tipshelp);
		tipshelp->loadFromFile(".resources/gui/ucurses_command_display");
		win->addTip("n: Advance ");
		win->addCommand('n', std::bind(&Intro::Tab, win));

	}
	
	void Intro::showTitle(Window* win)
	{
		win->clearCommands();
		Label* title = new Label(2, 1, win);
		win->addComponent(title);
		title->setText("^ Above this line is the title bar... mmm nice borders! ^");
		title->appendLine("Press 'c' to continue");
		win->addCommand('c', std::bind(&Intro::showTips, win));
	}

	void Intro::Tab(Window* win)
	{
		win->clearCommands();
		coord2d mid = win->getMiddle();
		Window* extra = win->subWindow(coord2d(60, 10), coord2d(50, 20));
		extra->setTitle("Extra window");
		extra->addTip("Enter: Do something");
		extra->addCommand(10, std::bind(&Intro::Extra, extra));
		win->Clear();	
		Label* text = new Label(3, 6, win);
		text->loadFromFile(".resources/gui/tabs_demo");
		win->addComponent(text);
	}

	void Intro::Extra(Window* win)
	{
		win->clearCommands();
		Label* text = new Label(3, 3, win);
		text->setText("This window is no longer needed.");
		text->appendLine("Press f2 to destroy this window.");
		win->addComponent(text);
	}
}
