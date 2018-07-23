#include <ucurses/component/Canvas.hpp>

#include <fstream>


namespace ucurses { 

	Canvas::Canvas(Window* win, coord2d size) : Component(win, coord2d{0,0}), cells(size.x, size.y) 
	{
        setSize(size.x, size.y);
        for (int y = 0; y < size.y; ++y)
            for (int x = 0; x < size.x; ++x)
                cells.data.emplace_back();
	}

	/*
	   void Canvas::loadFromText(const std::string& filepath)
	   {
	   if (data == nullptr)
	   {
	   std::fstream text(filepath, ios_base::in);
	   data = new ArrayXc(size.x, size.y);

	   for (int y = 0; y < size.y; y++)
	   for (int x = 0; x < size.x + 1; x++) // Read and discard \n 
	   {
	   char c;
	   text.get(c);
	   if (c != '\n')
	   data->(x,y) = c;
	   }
	   }
	   */

    void Canvas::Draw()
    {
        for (int y = 0; y < size.y; y++)
        {
            setCursor(0, y);
            for (int x = 0; x < size.x; x++)
            {
                Cell* cell = cells.Get(x, y);
                print(cell);
            }
        }
    }

}
