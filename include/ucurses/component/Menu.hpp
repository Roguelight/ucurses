// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * UCurses menu interface 
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <vector>

namespace ucurses { 

    #define NONE -1

	class Menu : public Component
    {
        using index = short;

		public:
        
            using Ptr = Menu*;

            Menu(coord x, coord y, Window* host);
            
            virtual void bindDefault();

            string getSelectedItem();           
            index getSelectedIndex();
            void addItem(const string& label);
            void removeAll();

        protected:

            /* Items */
            std::vector<string> items; 

            void removeItem(index id);
            string& getItem(index id);  // Performs bounds checking
    
            /* Selection */
            
            index selection;
            bool last()                                { return (selection + 1) == items.size(); }
            
            virtual void Update();

            void removeSelectedItem(); // *->BACKSPACE
            void selectNext();         // *->j
            void selectPrevious();     // *->k
	};

}
