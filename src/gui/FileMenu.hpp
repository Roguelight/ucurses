// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Menu.hpp>
#include <ctk/file/Directory.hpp>

using namespace ctk::file;

namespace ncursespp { namespace gui {

	class FileMenu : public Menu
	{
		public:

            FileMenu(coord x, coord y, Window* host);

        protected:

            void Update();

            string directory; // File directory from which files are displayed
            string last;      // History of one to enable backtracking
            void setDirectory(string inString);
            

            // Command functions
            virtual void bindDefault();
            void         printCommands();

            void         backTrack(); // Backtrack to last visited directory
            void         toParent();  // Navigate to parent directory
            virtual void Select();

	};

}};
