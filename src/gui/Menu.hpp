// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * Menu interface that is constructed as a Window Component.
 */

#pragma once
#include <ucurses/gui/Component.hpp>
#include <vector>
        

namespace ucurses { namespace gui {

    #define NONE -1
    using index = short;

	class Menu : public Component
    {
		public:

            Menu(coord x, coord y, Window* host);
            
            virtual void bindDefault();

            string getSelectedItem();           
            index getSelectedIndex();
            void addItem(string label);

        protected:

            /* Items */
            std::vector<string> items; 

            void removeItem(index id);
            string& getItem(index id);      // Performs bounds checking
            void removeAll();
    
            /* Selection */
            
            index selection;
            bool last()                                { return (selection + 1) == items.size(); }
            
            virtual void Update();

            // Command Functions:
            
            virtual void printCommands();
            
            void removeSelectedItem(); // *->BACKSPACE
            void selectNext();         // *->j
            void selectPrevious();     // *->k
	};

}}
