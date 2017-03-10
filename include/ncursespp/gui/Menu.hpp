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

            Menu(coord2d size, coord2d pos);

            string getSelectedItem();           
            index getSelectedIndex()            { return selection; }

        protected:

            /* Items */
            std::vector<string> items; 

            void addItem(string label);
            void removeItem(index id);
            string& getItem(index id);      // Performs bounds checking
    
            /* Selection */
            
            index selection;
            bool last()                                { return (selection + 1) == items.size(); }
            
            virtual void Update();

            // Command Functions:
            
            virtual void bindDefault();
            virtual void printCommands();
            
            virtual void Select() = 0; // * Different behaviour for selecting an item, mapped to enter
            void removeSelectedItem(); // *->BACKSPACE
            void selectNext();         // *->j
            void selectPrevious();     // *->k
	};

}}
