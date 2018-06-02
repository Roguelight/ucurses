#include <ucurses/component/Canvas.hpp>

#include <fstream>


namespace ucurses { 

	Canvas::Canvas(Window* win, coord x, coord y) : Component(win, x, y), data(nullptr)
	{

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

	void Canvas::setTarget(const ArrayXc* target, coord xsize, coord ysize) 
	{
		data = target; 
		setSize(xsize, ysize);
	}

	void Canvas::setTarget(const ArrayXc* target, coord2d size)
	{
		data = target; 
		setSize(size);
	}

	void Canvas::Draw()
	{
		if (data)
		{
			for (int y = 0; y < size.y; y++)
			{
				setCursor(0, y);
				for (int x = 0; x < size.x; x++)
					print(data->operator()(x,y));
			}
		}
	}

}
