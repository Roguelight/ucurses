#include <ucurses/gui/Config.hpp>

namespace ucurses { 
 
	std::string Config::config = ".resources/config/color_scheme.conf";

	void Config::Display(Window* win)
	{
		win->Clear();
		coord2d mid = win->getMiddle();

		SliderMenu* menu = new SliderMenu(mid.x - 10, mid.y, win);

		basic_slider& fore = menu->addItem("Foreground Color");
		basic_slider& back = menu->addItem("Background Color");
		basic_slider& primary = menu->addItem("Highlight Color");

		fore.setLimit(250.f);
		primary.setLimit(250.f);
		back.setLimit(250.f);

		if (!LoadSliders(menu))
		{
			primary.setValue(4.f);
			fore.setValue(5.f);
		}

		win->addCommand('l', bind( &Config::RefreshUI, win, menu));
		win->addCommand('h', bind( &Config::RefreshUI, win, menu));
        win->addCommand(10, bind( &Config::Escape, win, menu));
		win->addTip("Enter: Confirm");
	}

	void Config::Escape(Window* win, SliderMenu* menu)
	{
		Save(menu);
		win->Escape();
	}

	void Config::RefreshUI(Window* win, SliderMenu* menu)
	{
		short fore = static_cast<short>(menu->getItem(0).getValue());
		short back = static_cast<short>(menu->getItem(1).getValue());
		short primary = static_cast<short>(menu->getItem(2).getValue());
		init_pair(win->getColor(), fore, back);
		init_pair(2, primary, back);
		
	}
			
	void Config::Save(SliderMenu* menu)
	{
		ofstream file(config, ios_base::out);

		for (auto& slider : menu->getItems())
			file << slider.getValue() << std::endl;
	}

	bool Config::LoadSliders(SliderMenu* menu)
	{
		ifstream file(config, ios_base::in);
	
		if (file.good())
		{
			for (auto& slider : menu->getItems())
			{
				float f;
				file >> f;
				slider.setValue(f);
			}
			return true;
		}
		else
			return false;
	}

	void Config::Load()
	{
		ifstream file(config, ios_base::in);
		if (file.good())
		{
			float values[3]; 

			for (int i = 0; i < 3; ++i)
				file >> values[i];

			init_pair(1, values[0], values[1]);
			init_pair(2, values[2], values[1]);
		}
	}
}
