#include <ucurses/component/Checklist.hpp>

namespace ucurses {

    Item::Item(const std::string& inID) : id(inID), checked(false) 
    {
    
    }

    std::string Item::String()
    {
        if (checked)
            return id + " *";
        else
            return id;
    }
        
    size_t Item::length() const
    {
        size_t size = id.length();

        if (checked)
            size += 2;

        return size;
    }

    void Item::Check() 
    {
        checked = !checked;
    }
	
    Checklist::Checklist(Window* host, coord x, coord y) : Component(host, x, y)
    {

    }

    void Checklist::checkSelected()
    {
        getSelectedItem().Check();
    }

    void Checklist::bindDefault()
	{
		addCommand('j', bind( &menu_template::selectNext, this));                   // Move down menu 
		addCommand('k', bind( &menu_template::selectPrevious, this));               // Move up Menu 
	}
    
    void Checklist::Draw()
	{
		for (auto& item : items)
		{
			print(item.String());
			setCursor(0, getCursor().y + 1);
		}

		if (selection != NOSELECT)
		{
			int size = getSelectedItem().length();
			highlightWord(coord2d(0, selection), size, highlightColor, A_BOLD);
		}
	}
    
    void Checklist::Process(int input)
	{
		switch (input)
		{
			case 'j':
				selectNext();
				break;
			case 'k':
				selectPrevious();
				break;
            case 10:
                checkSelected();
                break;
		}
	}
    
    void Checklist::selectNext()
	{
		menu_template<Item>::selectNext();
		if (onRefresh)
			onRefresh();
	}
			
	void Checklist::selectPrevious()
	{
		menu_template<Item>::selectPrevious();
		if (onRefresh)
			onRefresh();
	}
            
    const std::string& Checklist::getSelectedText() const
    {
        return getSelectedItem().id;
    }


}
