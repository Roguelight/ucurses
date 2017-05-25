// Copyright Thu Feb 23 23:12:00 2017
// Liam Rogers, All rights reserved.

/*
 * UCurses menu that displays files in a specified directory
 */

#pragma once
#include <ucurses/component/Menu.hpp>
#include <ctk/file/Directory.hpp>
#include <ctk/log/GlobalLogger.hpp>


namespace ucurses { 

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

            void backTrack(); // Backtrack to last visited directory
            void toParent();  // Navigate to parent directory

	};

};
