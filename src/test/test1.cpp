#include <ucurses/tests/TestClass.hpp>
#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main(int argc, char* argv[])
{

    //ucurses::TestClass test;
    
    ucurses::GUI gui; // Initialize ucurses

    Window::Ptr win = gui.createWindow();
    /* No parameter overload for full screen */
    
    //Window::Ptr win = gui.createWindow(coord2d(50,20),coord2d(5,5)); 
    /* Specify size and position x,y coordinates respectively */

    mainScreen(win);
    
    //test.Run();
    gui.Run();


   
	
}
