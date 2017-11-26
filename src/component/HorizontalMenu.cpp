#include <ucurses/component/HorizontalMenu.hpp>

namespace ucurses {

	HorizontalMenu::HorizontalMenu(Window* target, coord x, coord y) : Menu(target, x, y)
	{
		//bindDefault();
	}

	void HorizontalMenu::bindDefault()
	{
		// Vim keys ftw
		addCommand('l', bind( &Menu::selectNext, this));
		addCommand('h', bind( &Menu::selectPrevious, this));
	}

	void HorizontalMenu::Process(int input)
	{
		switch (input)
		{
			case 'l':
				selectNext();
				break;
			case 'h':
				selectPrevious();
				break;
		}
	}

	void HorizontalMenu::Draw()
	{
	
		for (auto& item : items)
		{
			print(item);
			print(std::string(" "));
		}
		
		if (selection != NOSELECT)
		{
			int size = getSelectedItem().length();
			int position = 0;
			for (int i = 0; i < selection; ++i)
				position += items[i].length() + 1;

			highlightWord(coord2d(position, 0), size, highlightColor, A_BOLD);
		}
	}

}

