#include <gui/Config.hpp>

namespace ucurses { 


	void Config::Display(Window* win)
	{
		win->Clear();
		coord2d mid = win->getMiddle();

		SliderMenu* menu = new SliderMenu(mid.x - 10, mid.y, win);

		basic_slider& fore = menu->addItem("Main Foreground Color");
		fore.setLimit(250.f);
		fore.setValue(8.f);

		basic_slider& primary = menu->addItem("Primary Highlight Color");
		primary.setValue(4.f);
		primary.setLimit(250.f);
		basic_slider& sec = menu->addItem("Secondary Highlight Color");
		sec.setLimit(250.f);

		win->addCommand('l', bind( &Config::RefreshUI, win, menu));
		win->addCommand('h', bind( &Config::RefreshUI, win, menu));
        win->addCommand(10, bind( &Window::Escape, win));
		win->addTip("Enter: Confirm");
	}

	void Config::RefreshUI(Window* win, SliderMenu* menu)
	{
		short fore = static_cast<short>(menu->getItem(0).getValue());
		short primary = static_cast<short>(menu->getItem(1).getValue());
		short secondary = static_cast<short>(menu->getItem(2).getValue());
		init_pair(win->getColor(), fore, 0);
		init_pair(2, primary, secondary);
		
	}
}
