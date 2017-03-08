// Copyright Wed Mar  8 02:49:05 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Window.hpp>
namespace ncursespp { namespace gui {

	class TextEntry : public Window
	{
		public:

			TextEntry(coord2d size, coord2d pos);



        private:

            virtual void Update();

	};

}}
