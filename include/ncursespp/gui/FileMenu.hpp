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

			FileMenu();
            FileMenu(coord2d size, coord2d position);

            void setDirectory(string dir)     { directory = dir; }

            virtual void Update();


        protected:

            void refreshList();
            string directory;

	};

}};
