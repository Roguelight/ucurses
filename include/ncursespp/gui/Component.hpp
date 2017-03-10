// Copyright Thu Mar  9 22:35:08 2017
// Liam Rogers, All rights reserved.

/*
 * Stores Update() method and position in which the component
 * should be updated from in the host window
 *
 * Avoiding making UIComponent a polymorphic class to reduce 
 * overhead of vectors and pointer traversing. As a result,
 * classes inheriting from Window will have to interface with
 * the components directly, instead of add them to a vector<UIComponent*>
 */

#pragma once
#include <ncursespp/gui/Window.hpp>

namespace ncursespp { namespace gui {

	class Component
	{
        friend class Window;

		public:

		    Component(coord2d size, coord x, coord y, Window* host);


        protected:

            virtual void Update() = 0;
            virtual void printCommands();

            coord2d pos;  // Position in host window
            coord2d size; // Indicates where to stop printing
            string  ID; 

            Window* H_Window;

	};

}}
