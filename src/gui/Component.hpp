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
#include <ncursespp/gui/Window.hpp>

namespace ncursespp { namespace gui {

	class Component
	{
		public:

			Component(coord x, coord y, Window* host);

        protected:

            /* Update */

            virtual void Update() = 0;
            Window*      H_Window;     // Handle to host

            /* Manipulation */

            void print(string inString); 
            void move(coord x, coord y);        // Move relative to current position
            void setPostiion(coord x, coord y); // Set absolute position
            void setSize(coord x, coord y);
            coord2d  getMiddle() const; 

            coord2d position;
            coord2d size;

            // Attributes

            void attributeOn(int attributes);
            void attributeOff(int attributes);

            /* Commands : Windows parse the commands of all their components */

            void addCommand(int key, delegate func);

            // Hosts have the option of constructing their own bindings or using default
            virtual void bindDefault() = 0;
            void commandPrintPos();
	};

    
}}
