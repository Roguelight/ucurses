#include <sstream>

namespace ucurses { namespace ArrayUI {

	template<typename T>
	void Display(Window* win, const ctk::Array<T>& lib, coord2d pos)
	{
        win->setTitle("Array Interface");
        
		TextEntry* search = new TextEntry(pos.x, pos.y + 3, win);
        search->setSubject("Linear Search");
        
		Menu* list = new Menu(pos.x, pos.y + 5, win);
        
		for (auto element : lib.getData())
            list->addItem(element.getName());
        
		Label* display = new Label(pos.x + 30, pos.y, win);
        
		win->addCommand('S', bind(Search<T>, lib, search, display));
        win->addCommand(10, bind(Select<T>, lib, list, display));
        
		win->addTip("S: Search Array"); 
        win->addTip("Enter: Display Selected");
	}
	
	template<typename T>
	void Search(const ctk::Array<T>& lib, TextEntry* search, Label* display)
	{
        const T* element = lib.Get(search->getText()); // Linear search for element
        display->Clear();

        if (element != nullptr)
			Update(display, *element); // T element must have overloaded operator<<
		else
			search->setText("Not found");
	}
	
	template<typename T>
	void Select(const ctk::Array<T>& lib, Menu* select, Label* display)
	{
        const T* element = lib.Get(select->getSelectedItem());
		display->Clear();

        if (element != nullptr)
			Update(display, *element);
	}
	
	template<typename T>
	void Update(Label* display, T& obj)
	{
		std::stringstream ss;
		ss << obj;
		display->setText(ss.str());
	}
}}
