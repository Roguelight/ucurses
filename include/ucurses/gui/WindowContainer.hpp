// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ucurses/gui/Window.hpp>

namespace ucurses { namespace gui {

    class WindowContainer 
    {
        using WindowMap = std::map<string, Window*>;  // map of pointers allows needed flexibility for GUI hierarchy

        public:
            
            WindowContainer();
            virtual ~WindowContainer();
            
            void UpdateAll();
            void UpdateActive();
            void Refresh();
            void Add(string ID, Window* win);
            void Remove(string ID);
            void RemoveAll();
            
            void Next();
            /*
             * Sets active window to next window in map
             */ 


            Window* Get(string ID) const;
            Window* getActive() const       { return active.second; }
            void Parse(int input);

        private:

            WindowMap M_Windows;
            std::pair<string, Window*> active;
            

            ColorContainer Colors;


    };

}}
