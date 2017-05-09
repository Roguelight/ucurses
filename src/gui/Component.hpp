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

#include <ucurses/gui/types.hpp>
#include <ucurses/gui/Command.hpp>

using namespace std;

namespace ucurses { namespace gui {
    class Window;
	class Component
	{
        friend class Window;
        friend class ComponentArray;
		public:
            
            /* Constructor */ // Default sizes are set by children
			Component(coord x, coord y, Window* host);

        protected:

            /* Update */

            virtual void Update() = 0;
            Window*      H_Window;     // Handle to host

            /* Manipulation */

            void print(string inString); 
            void move(coord x, coord y);        // Move relative to current position
            void setPosition(coord x, coord y); // Set absolute position
            void setSize(coord x, coord y);
            coord2d  getMiddle() const; 
            coord2d  getPos()    const;

            coord2d position;
            coord2d size;

            // Attributes

            void attributeOn(int attributes);
            void attributeOff(int attributes);
            
            // Highlighting
            void highlightWord(coord2d wordpos, int size);                  
            void highlightRow(coord row);                  
            void highlightColumn(coord column);                  

        public:

            /* Commands : Windows parse the commands of all their components */

            void addCommand(int key, delegate func);

            // Hosts have the option of constructing their own bindings or using default
            virtual void bindDefault() = 0;
            void printPosition();
	};

    
}}
