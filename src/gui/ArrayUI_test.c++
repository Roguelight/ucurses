

#include <ucurses/ucurses.hpp>
#include <ctk/storage/Array.hpp>
#include <ctk/external/material_data.hpp>

using namespace ucurses;
using namespace ctk;

int main()
{
	UCurses gui;
	Window* mainwindow = gui.createWindow();

	ctk::Array<material_data> arr;

	arr.Load("./array", Format::BINARY);

    ucurses::ArrayUI::Display(mainwindow, arr);
	gui.Run();
}
