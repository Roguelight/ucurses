#include <ucurses/ucurses.hpp>
#include <ctk/storage/Array.hpp>
#include <ctk/external/material_data.hpp>

using namespace ctk;
using namespace ucurses;

int main()
{
	UCurses gui;
	Window* mainwindow = gui.createWindow();

	ctk::Array<material_data> arr;

	arr.Load("./array", Format::BINARY);

	ArrayInterface<material_data> interface(arr);
	interface.Bind(mainwindow);

	gui.Run();	
}
