/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>

namespace ucurses { namespace DataUI {


	template<typename T>
	void Display(Window* win, const T& data, coord2d pos = coord2d(2,2));

	template<typename T>
	void Search(const T& data, TextEntry* search, Label* display);
	
	template<typename T>
	void Select(const T& data, Menu* select, Label* display);
	
	template<typename T>
	void Update(Label* display, T& obj);

}}

#include <ucurses/gui/ArrayUI_def.hpp>
