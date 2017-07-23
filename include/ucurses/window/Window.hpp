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
#include <algorithm>

#include <ctk/log/GlobalLogger.hpp>

#include <ucurses/window/types.hpp>
#include <ucurses/window/Color.hpp>

#include <ucurses/command/Command.hpp>
#include <ucurses/component/ComponentArray.hpp>

#include <ncurses.h>

using namespace std;
using namespace ctk::log;

namespace ucurses { 

	class UCurses;
	class Window
	{
        friend class WindowContainer;
        friend class Component;

        public:
            
            using Ptr = Window*;
			static UCurses* ucurses; // Static object for creating new windows
           
            Window(bool deletable = false); 
            Window(coord2d size, coord2d position, bool deletable = false); // Specifies size and position within NCurses stdscr
			~Window();

            void addComponent(Component* component);
            void addCommand(int key, delegate func);
            void setCallback(int key, delegate func);
			void setCallbackTip(const string& in)		{ callback_tip = in; }
            void addTip(string& tip);
            void addTip(string&& tip);
            void Clear(); // Destroys all components and commands
            void clearCommands(); 
            void clearComponents(); 

			Window* subWindow(coord2d size, coord2d pos);

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
			std::vector<string> tips;
			Command callback;
			string callback_tip;

            void printCommands(); 

            /* Components */

            ComponentArray Components;
			
        private:

            WINDOW* H_Window;      // Direct handle to NCurses WINDOW data

            string title;
			bool deletable;

            static ColorContainer* S_Colors;
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
