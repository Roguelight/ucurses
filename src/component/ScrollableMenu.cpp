#include <ucurses/component/ScrollableMenu.hpp>
#include <ctk/math/unary_integral.hpp>

namespace ucurses {

	ScrollableMenu::ScrollableMenu(Window* host, coord x, coord y)
	{
	
	}

    /*
     * Only draw nShown items, with menu_template::selection in the middle
     */
    void ScrollableMenu::Draw()
    {
        for (int i = selection - range; i < selection + range; ++i)
        {
            if (i < 0) i = 0;
            if (i < items.size())
            {
			    print(items[i]);
			    setCursor(0, getCursor().y + 1);
            }
        }
		
        if (selection != NOSELECT)
		{
			int size = getSelectedItem().length();
			highlightWord(coord2d(0, selection), size, highlightColor, A_BOLD);
		}
    }

    void ScrollableMenu::setRange(short s)
    {
        ctk::cap(s, 50);
        range = (s /2);
    }
}
