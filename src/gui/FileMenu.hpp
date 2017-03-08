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

            FileMenu(coord2d size, coord2d position);

        protected:

            string directory;

            string last;
            // History of one to enable backtracking
            
            void setDirectory(string inString);
            void backTrack();
            
            virtual void Select();
            virtual void addCommands();

	};

}};
