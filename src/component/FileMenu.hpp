/*
 * UCurses menu that displays files in a specified directory
 */

#pragma once
#include <ucurses/component/Menu.hpp>
#include <ctk/file/Directory.hpp>

namespace ucurses { 

	class FileMenu : public Menu
	{
		public:

			FileMenu(coord x, coord y, Window* host);

			void setDirectory(string inString);

		protected:

			string directory; // File directory from which files are displayed
			string last;      // History of one to enable backtracking

			// Command functions

			void backTrack(); // Backtrack to last visited directory
			void toParent();  // Navigate to parent directory

	};

};
