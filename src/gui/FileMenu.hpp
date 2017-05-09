// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ucurses/gui/Menu.hpp>
#include <ctk/file/Directory.hpp>

using namespace ctk::file;

namespace ucurses { namespace gui {

	class FileMenu : public Menu
	{
		public:

            FileMenu(coord x, coord y, Window* host);
            
            virtual void bindDefault();
            void setDirectory(string inString);

        protected:

            void Update();

            string directory; // File directory from which files are displayed
            string last;      // History of one to enable backtracking
            
            // Command functions
            //
            void         printCommands();

            void         backTrack(); // Backtrack to last visited directory
            void         toParent();  // Navigate to parent directory

	};

}};
