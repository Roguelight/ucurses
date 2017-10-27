// Copyright Fri Mar 10 15:36:09 2017
// Liam Rogers, All rights reserved.

/*
 * Polymorphic widgets that give host windows dynamic behaviour
 *
 * Abstract virtual Update() overidden for varied display behaviour
 * Provides interface to window host display methods that use relative positioning.
 *
 * Supports inheritance
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

			/* Constructors */ 

			/*
			 * Components cannot be constructed without handle to parent window
			 * This is because windows are responsible for cleaning up dynamically allocated
			 * gui components.
			 */

			Component(Window* host, coord x = 0, coord y = 0);		
			Component(Window* host, coord2d pos = {0,0});			
			Component(Window* host);						

			/* Commands */

			void addCommand(int key, delegate func);
			void addTip(string& tip);
			void addTip(string&& tip);

			/* Component Manipulation */

			void setSize(coord x, coord y);
			void setSize(coord2d size);
			void setPosition(coord x, coord y);
			void setPosition(float x, float y);				/* Sets x and y based on percentage of window size */
			
			coord2d getSize();

			/* Attributes */

			void attributeOn(int attributes);
			void attributeOff(int attributes);

			/* Highlighting */

			void highlightWord(coord2d wordpos, int size, short color = 0, attr_t attributes = A_BOLD);
			void highlightRow(coord row, short color = 0, attr_t attributes = A_BOLD);                  
			void highlightColumn(coord column, short color = 0, attr_t attributes = A_BOLD);                  
			void highlightChar(coord2d pos, short color = 0, attr_t attributes = A_BOLD);                  

			void setHighlight(short color);
			void setColor(short color);						/* Sets component color */

		protected:

			/* Cursor Manipulation */

			void setCursor();								/* Set window cursor position to component position */
			void setCursor(coord x, coord y);				/* Set window cursor relative to component position */
			void moveCursor(coord x, coord y);        		/* Move window cursor relative to current position */
			void print(const std::string& inString); 
			void print(char c);
			void print(char* c);

			/* Getters */

			coord2d  getMiddle() 	const; 
			coord2d  getCursor()  	const;
			coord2d  getPosition()  const;

			void Update();
			virtual void Draw() = 0;						/* Called in Update() to render component to window */
			virtual void bindDefault() 	{}					/* Children can construct their own bindings or using default */
			virtual void Process(int input) 		{}

			coord2d position;
			coord2d size;
			short highlightColor;
			short color;

			Window*      H_Window;     						/* Handle to host */
	};
}
