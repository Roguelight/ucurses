/*
 * UCurses File menu with navigation commands
 *
 */

#pragma once
#include <ucurses/gui/FileMenu.hpp>

namespace ucurses { namespace gui {

	class FileNav : public FileMenu
	{
		public:

            FileNav(coord x, coord y, Window* host);

            virtual void bindDefault();

        protected:

            virtual void Select();

	};

}}
