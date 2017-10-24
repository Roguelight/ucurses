/*
 * UCurses File menu with navigation commands
 *
 */

#pragma once
#include <ucurses/component/FileMenu.hpp>

namespace ucurses { 

	class FileNav : public FileMenu
	{
		public:

			FileNav(Window* host, coord x = 0, coord y = 0);

			virtual void bindDefault();

		protected:

			virtual void Select();

	};

}
