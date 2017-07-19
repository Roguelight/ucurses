// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

/*
 * Window provides an interface for manipulating NCurses WINDOW 
 * structure and mapping commands to keys
 * 
 * Constructor is exposed through the ucurses::GUI object. Window* handle = gui.createWindow();
 * This ensures safe initialization and storage.
 */

#pragma once
#include <string>
#include <map>
#include <functional>
#include <algorithm>

#include <ctk/log/GlobalLogger.hpp>

#include <ucurses/window/types.hpp>
#include <ucurses/window/Color.hpp>

#include <ucurses/command/Command.hpp>
#include <ucurses/command/Display.hpp>

#include <ucurses/component/ComponentArray.hpp>

#include <ncurses.h>

using namespace std;
using namespace ctk::log;

namespace ucurses { 

	class Window
	{
        friend class WindowContainer;
        friend class Component;

        public:
            
            using Ptr = Window*;
           
            Window(); 
            Window(coord2d size, coord2d position); // Specifies size and position within NCurses stdscr
			~Window();

            void addComponent(Component* component);
            void addCommand(int key, delegate func);
            void addTip(string& keyID, string& funcID);
            void addTip(string&& keyID, string&& funcID);
            void Clear(); // Destroys all components and commands

        protected:
    
            /* Construction */

            void resize(coord2d size, coord2d position);

            /* Manipulation */

            void  setPosition(coord x, coord y); // Sets cursor to absolute position
            void  move(coord x, coord y);        // Moves cursor to relative to current position      
            void  print(string inString);        // Prints from current cursor position

            /* Attributes */

            void setAttributes(int attributes);
            void attributeOn(int attributes);
            void attributeOff(int attributes);
           
            /*  Highlighting */

            void highlightWord(coord2d wordpos, int size);                  
            void highlightRow(coord row);                  
            void highlightColumn(coord column);                  
            
            /* Update */
            
            void Update();
            void printBorder();

        public:

            /* Retrieval Methods */
            
            coord2d   getSize()         const;
            coord2d   getPosition()     const;
            coord2d   getMiddle()       const; 
            
            WINDOW*  getHandle()  const;
            string   getTitle()   const;
            void setTitle(string s);
   
        protected:

            /* Commands */
            
            CommandArray Commands;
            command::Display CommandMap;

            void printCommands(); 

            /* Components */

            ComponentArray Components;
			
        private:

            WINDOW* H_Window;      // Direct handle to NCurses WINDOW data

            string title;

            const  ColorContainer* S_Colors;
            void   EnableColor(ColorContainer* s_ptr);
            
            friend bool operator==(const Window& lhs, const string& rhs) 
            { 
                if (lhs.getTitle() == rhs)
                    return true;
                else
                    return false;
            }

	};

}
