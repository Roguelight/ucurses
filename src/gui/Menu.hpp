// Copyright Sun Feb 19 02:12:50 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Window.hpp>
#include <vector>

namespace ncursespp { namespace gui {

	class Menu : public Window
	{
		public:

			Menu();
            Menu(coord2d size, coord2d position);

            virtual void Update();

            void addItem(string label);
            void selectItem(index id)          { selection = id; }
            string& getSelectedItem()       { return getItem(selection); }
            string& getItem(index id);

            void clear();


        protected:

            std::vector<string> items; 
            index selection;

	};

}}
