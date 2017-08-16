// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * UCurses menu interface 
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/menu_template.hpp>
#include <vector>

namespace ucurses { 

#define NOSELECT -1

	class Menu : public Component, public menu_template<std::string>
	{
		public:

			Menu(coord x, coord y, Window* host);

			virtual void bindDefault();
			void showHelp();

		protected:

			virtual void Draw();

	};

}
