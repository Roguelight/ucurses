// Copyright Fri Mar 10 01:47:42 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Window.hpp>

namespace ncursespp { namespace gui {

    class WindowContainer 
    {
        friend class ncursespp::application::GUI;
        
        using WindowMap = std::map<string, Window*>;  // map of pointers allows needed flexibility for GUI hierarchy

        public:
            
            WindowContainer();
            virtual ~WindowContainer();
            
            void UpdateAll();
            void UpdateActive();
            void Refresh();
            void Add(string ID, Window* win);
            void Remove(string ID);

            /*
             * Sets active window to next window in map
             */ void Next();


            Window* Get(string ID) const;
            Window* getActive() const       { return active.second; }

        private:

            WindowMap M_Windows;
            std::pair<string, Window*> active;
            

            ColorContainer Colors;

            void Parse(int input);

    };

}}
