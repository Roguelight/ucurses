// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * Menu interface that uses the ncurses WINDOW data structure.
 * The original ncurses menu written in C is ugly to use so I implemented
 * my own
 */

#pragma once
#include <ncursespp/gui/Window.hpp>
#include <vector>
        

namespace ncursespp { namespace gui {

    #define NONE -1
    using index = short;

	class Menu : public Window
	{
		public:

            Menu(coord2d size, coord2d position);

            void addItem(string label);
            void removeItem(index id);
            void removeSelectedItem();
            string& getItem(index id);      // Performs bounds checking

            inline void selectItem(index id)           { selection = id;            }
            inline string& getSelectedItem()           { if (selection != NONE) return getItem(selection); }
            inline index getSelectedIndex()            { if (selection != NONE) return selection; }

        protected:

            std::vector<string> items; 
            index               selection;
            /*
             * Selection ranges from 0-max
             * 0 indicates no item selected
             */
            
            virtual void Update();
            virtual void addCommands();

            virtual void Select() = 0; 
            /*
             * Different behaviour for selecting an item, mapped to enter
             */

            void selectNext();
            void selectPrevious();
            bool last()            { return (selection + 1) == items.size(); }
	};

}}
