#include <ucurses/gui/Config.hpp>
#include <ucurses/ucurses.hpp>

namespace ucurses { 
 
	std::string Config::config = ".resources/config/color_scheme.conf";

	void Config::Initialize()
	{
		coord2d mid = target->getMiddle();

		menu = new SliderMenu(target);
        menu->print_numeric = true;
		menu->setPosition(0.5f, 0.5f);

		basic_slider& fore = menu->addItem("Foreground Color");
		basic_slider& back = menu->addItem("Background Color");
		basic_slider& primary = menu->addItem("Highlight Color");

		fore.setLimit(250.f);
		primary.setLimit(250.f);
		back.setLimit(250.f);

		if (!LoadSliders())
		{
			primary.setValue(4.f);
			fore.setValue(5.f);
		}

		target->Commands.Add('l', bind( &Config::RefreshUI, this));
		target->Commands.Add('h', bind( &Config::RefreshUI, this));
        target->Commands.Add(10, bind( &Config::Escape, this));
		target->addTip("Enter: Confirm");
	}

	void Config::Escape()
	{
		Save();
		target->Escape();
	}

	void Config::RefreshUI()
	{
		short fore = static_cast<short>(menu->getItem(0).getValue());
		short back = static_cast<short>(menu->getItem(1).getValue());
		short primary = static_cast<short>(menu->getItem(2).getValue());
		init_pair(target->getColor(), fore, back);
		init_pair(2, back, primary);
		
	}
			
	void Config::Save()
	{
		ofstream file(config, ios_base::out);

		for (auto& slider : menu->getItems())
			file << slider.getValue() << std::endl;
	}

	bool Config::LoadSliders()
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

	void Config::Load(const std::string& filepath)
	{
		ifstream file(filepath, ios_base::in);
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
