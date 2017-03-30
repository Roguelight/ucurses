// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

/*
 * Window provides an interface for manipulating NCurses WINDOW 
 * structure and mapping commands to keys
 *
 * Children of window are responsible for constructing appropriate
 * UIComponents (Non polymorphic) and mapping appropriate commands
 * to achieve desired interface behaviour.
 */

#pragma once
#include <string>
#include <map>
#include <functional>
#include <algorithm>

#include <ctk/log/GlobalLogger.hpp>

#include <ncursespp/gui/types.hpp>
#include <ncursespp/gui/Color.hpp>
#include <ncursespp/gui/Command.hpp>
#include <ncursespp/gui/Components.hpp>

#include <ncurses.h>

using namespace std;
using namespace ctk::log;

namespace ncursespp { namespace application {
    class GUI;
}}

using namespace ncursespp::application;

namespace ncursespp { namespace gui {

	class Window
	{
        friend class WindowContainer;
        friend class Component;

		public:

            Window(); // Default constructor initialises H_Window to NCurses stdscr
            Window(coord2d size, coord2d position); // Specifies size and position within NCurses stdscr
			virtual ~Window();

        protected:
    
            /* Update */
            
            virtual void Update();
            void printBorder();
            WINDOW* H_Window;      // Direct handle to NCurses WINDOW data
            /*
             * H_ prefix indicates handle ownership and thus the data should be 
             * manage elsewhere
             */

            /* Construction */

            void resize(coord2d size, coord2d position);
            void setTitle(string s);

            /* Manipulation */

            void  setPosition(coord x, coord y); // Sets cursor to absolute position
            void  move(coord x, coord y);        // Moves cursor to relative to current position      
            void  print(string inString);        // Prints from current cursor position

            // Attributes
            void setAttributes(int attributes);
            void attributeOn(int attributes);
            void attributeOff(int attributes);
           
            // Highlighting
            void highlightWord(coord2d wordpos, int size);                  
            void highlightRow(coord row);                  
            void highlightColumn(coord column);                  

        public:

            /* Retrieval Methods */
            
            coord2d   getSize()   const;
            coord2d   getPos()    const;
            coord2d   getMiddle() const; 
            
            WINDOW*  getHandle()  const;
            string   getTitle()   const;
            void addCommand(int key, delegate func);

        protected:

            /* Commands */
            
            CommandArray Commands;
           
            virtual void printCommands(); // Override for child Windows 
            void printGuiCommands();      // Prints application commands to Standard Screen 

            /* Components */

            ComponentArray Components;

            void Clear(); // Destroys all components and commands

        private:

            string title;
            bool   std; // Destructor variable, does not free space to prevent double deletion.
            const  ColorContainer* S_Colors;
            void   EnableColor(ColorContainer* s_ptr);

	};

}}
