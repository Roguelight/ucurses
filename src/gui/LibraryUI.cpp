#include <gui/LibraryUI.hpp>


namespace ucurses { namespace LibraryUI {

	template<typename T>
	void Display(Window* win, ctk::Library<T>& lib, coord2d pos)
	{
        win->setTitle("Library Interface");
        
		TextEntry* search = new TextEntry(pos.x, pos.y + 3, win);
        search->setSubject("Linear Search");
        search->bindDefault();
        
		Menu* list = new Menu(pos.x, pos.y + 4, win);
        
		for (auto data : library->getData())
            list->addItem(data.getName());
	
	}
}}
