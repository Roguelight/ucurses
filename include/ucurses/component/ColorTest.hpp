#include <ucurses/ucurses.hpp>

class ColorTest : public ucurses::Application
{
    public:
    
        ColorTest();
        void Update();

        ucurses::Label* some_text;
        ucurses::Label* colored_text;
        ucurses::Canvas* canvas;
        short color = 0;
    
};
