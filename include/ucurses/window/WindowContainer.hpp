// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

/*
 * Ensures updating of all windows
 * One per program, tracks active window and delegates commands
 */

#pragma once
#include <ucurses/window/Window.hpp>

namespace ucurses { 

    #define NONE -1

    class WindowContainer 
    {
        friend class UCurses;

        public:
           
            Window& operator[](int index) { return M_Windows[index]; }
            const Window& operator[](int index) const { return M_Windows[index]; }

            WindowContainer();
           	~WindowContainer(); 

            Window* Create(coord2d size, coord2d pos, bool deletable = false);
            Window* Create(bool deletable = false);

            void Remove(string ID);
            void RemoveActive();
            void RemoveAll();
            
            const Window& Get(string ID) const;
            Window& getActive();

        private:
            
            void Parse(int input);
            /*
             * Only passes input to active window
             */
            
            void Next();
            /*
             * Sets active window to next window in map
             */ 
            
            void UpdateAll();
            void UpdateActive();
            void Refresh();

            int getInput();

            vector<Window> M_Windows;
            index active; 
            
            ColorContainer Colors;

    };

}
