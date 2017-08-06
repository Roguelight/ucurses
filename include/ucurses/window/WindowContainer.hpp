/*
 * Ensures updating of all windows
 * One per program, tracks active window and delegates commands
 */

#pragma once
#include <ucurses/window/Window.hpp>

#define NOACTIVE -1
// Careful with macros, text also replaces variable definitions. Eg. enum Select { NONE = 0, ...};

namespace ucurses { 

    class WindowContainer 
    {
        friend class UCurses;

        public:
           
            Window& operator[](int index) 				{ return M_Windows[index]; }
            const Window& operator[](int index) const 	{ return M_Windows[index]; }

            WindowContainer();
           	~WindowContainer(); 

            Window* Create(coord2d size, coord2d pos);
            Window* Create();

            void Remove(const std::string& ID);
            void RemoveActive();
            void RemoveAll();
            
            const Window& Get(const std::string& ID) const;
            Window& getActive();

            void Process(int input);							/* Only passes input to active window */
            void Next();										/* Sets active window to next window in map */ 
            
            void UpdateAll();
            void UpdateActive();
            void Refresh();

            int getInput();

        private:

            vector<Window> M_Windows;
            index active; 
            
            ColorContainer Colors;

    };
}
