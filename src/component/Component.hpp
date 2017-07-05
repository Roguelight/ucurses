// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

/*
 * Constructed and destroyed at the same time as host
 *
 * Added commands are added to the hosts CommandArray
 * so the Component must not be destroyed before host
 *
 */

#pragma once
#include <ncurses.h>

#include <string>

#include <ucurses/command/Command.hpp>
#include <ucurses/window/types.hpp>
#include <ucurses/window/Window.hpp>

namespace ucurses { 

    using namespace std;

	class Component
	{
        friend class Window;
        friend class ComponentArray;

        public:
            
            /* Constructor */ // Default sizes are set by children
			Component(coord x, coord y, Window* host);

            /* Commands : Stored in host */

            void addCommand(int key, delegate func);
            void addTip(string keyID, string funcID);

            // Hosts have the option of constructing their own bindings or using default
            virtual void bindDefault() = 0;

        protected:

            /* Update */

            virtual void Update() = 0;

            /* Manipulation */

            void print(string inString); 
            void move(coord x, coord y);        // Move relative to current position

            /* Getters */
            
            /* Set position to component position */
            void setPosition();
            /* Set absolute position */
            void setPosition(coord x, coord y);
            void setSize(coord x, coord y);

            coord2d  getMiddle() const; 
            coord2d  getPosition()    const;


            // Attributes
            void attributeOn(int attributes);
            void attributeOff(int attributes);
            
            // Highlighting
            void highlightWord(coord2d wordpos, int size);                  
            void highlightRow(coord row);                  
            void highlightColumn(coord column);                  
           
            /* State */

            coord2d position;
            coord2d size;
            Window*      H_Window;     // Handle to host

	};

}
