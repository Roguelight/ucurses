// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

/*
 * File description
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

		public:

            Window(); //default constructor for stdscr
            Window(coord2d size, coord2d position);
			virtual ~Window();

            //inline
            
            void     move(coord2d pos)      { wmove(H_Window, pos.y, pos.x);        }
            void     print(string inString) { waddstr(H_Window, inString.c_str());  }
            
            WINDOW*  getHandle() const      { return H_Window;  }
            string   getTitle() const       { return title;     }
            void     setTitle(string s);

            coord2d  getSize() const;
            coord2d  getPos() const;

        protected:

            void addBorder();
            void resize(coord2d size, coord2d position);

            
            const ColorContainer* S_Colors;
            void  EnableColor(ColorContainer* s_ptr) { S_Colors = s_ptr; }
            
            void setAttributes(int attributes)      { wattrset(H_Window, attributes); }
            void setAttribute(int attributes)       { wattron(H_Window, attributes);  } 
            void attributeOff(int attributes)       { wattroff(H_Window, attributes); }
            
            void highlightWord(coord2d wordpos, int size);                  
            void highlightRow(coord row);                  
            void highlightColumn(coord column);                  
            
            string title;

            virtual void Update();

            void defaultCommands() {};

            CommandArray Commands;

        private:

            WINDOW* H_Window;
            /*
             * Use prefix H_ to indicate the pointer is a handler of some
             * data. This indicates this object is the sole owner of the
             * object on the heap and should be responsible for initialisation
             * and clean up of data.
             */
            bool std; // Destructor variable, does not free space to prevent double deletion.
	};


    class WindowContainer 
    {
        friend class ncursespp::application::GUI;
        
        using WindowMap = std::map<string, Window*>;  // map of pointers allows needed flexibility for GUI hierarchy

        public:
            
            WindowContainer();
            virtual ~WindowContainer();
            
            void Update();
            void Refresh();
            void Add(string ID, Window* win);
            void Remove(string ID);

            /*
             * Sets active window to next window in map
             */ void Next();


            Window* Get(string ID) const;
            Window* getActive() const       { return active.second; }

        private:

            WindowMap M_Windows;
            std::pair<string, Window*> active;
            

            ColorContainer Colors;

            void Parse(int input);

    };

}}
