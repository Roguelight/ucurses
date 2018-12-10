#include <ucurses/component/Canvas.hpp>

#include <fstream>


namespace ucurses { 

	Canvas::Canvas(Window* win, coord2d size) : Component(win, coord2d{0,0}), cells(size.x, size.y) 
	{
        setSize(size.x, size.y);
	}

    void Canvas::Clear()
    {
        cells.data.clear();
        for (int y = 0; y < size.y; ++y)
            for (int x = 0; x < size.x; ++x)
                cells.data.emplace_back(' ', 1);
    }

    void Canvas::Fill(char c, unsigned short color)
    {
        for (int y = 0; y < size.y; ++y)
            for (int x = 0; x < size.x; ++x)
                cells.data.emplace_back(c, color);
    }

    void Canvas::centerWindow()
    {
        int divisor = (spread ? 1 : 2);
        setPosition(0.5f, 0.5f);
        position.x -= size.x / divisor;
        position.y -= size.y / 2;
    }

    void Canvas::Draw()
    {
        for (int y = 0; y < size.y; y++)
        {
            setCursor(0, y);
            for (int x = 0; x < size.x; x++)
            {
                Cell* cell = cells.Get(x, y);
                print(cell);
                if (spread)
                    print(' ');
            }
        }
    }

    void Canvas::setSpread(bool b)
    {
        spread = b;
    }

}
