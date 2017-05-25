// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

/*
 * Ensures updating of all windows
 * One per program, tracks active window and delegates commands
 */

#pragma once
#include <ucurses/gui/Window.hpp>

namespace ucurses { 

    #define NONE -1

    class WindowContainer 
    {
        friend class GUI;

        public:
           
            Window& operator[](int index) { return M_Windows[index]; }
            const Window& operator[](int index) const { return M_Windows[index]; }
            WindowContainer();
            virtual ~WindowContainer();
            
            Window* Create(coord2d size, coord2d pos);
            Window* Create();

            void Remove(string ID);
            void RemoveAll();
            
            void Next();
            /*
             * Sets active window to next window in map
             */ 

            const Window& Get(string ID) const;
            const Window& getActive() const;

        private:
            
            void Parse(int input);
            /*
             * Only passes input to active window
             */
            
            void UpdateAll();
            void UpdateActive();
            void Refresh();

            vector<Window> M_Windows;
            index active; 
            
            ColorContainer Colors;

    };

}
