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

			FileNav(coord x, coord y, Window* host);

			virtual void bindDefault();

		protected:

			virtual void Select();

	};

}
