/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>
#include <ctk/storage/Array.hpp>

namespace ucurses { namespace ArrayUI {


	template<typename T>
	void Display(Window* win, const ctk::Array<T>& arr, coord2d pos = coord2d(2,2));

	template<typename T>
	void Search(const ctk::Array<T>& arr, TextEntry* search, Label* display);
	
	template<typename T>
	void Select(const ctk::Array<T>& arr, Menu* select, Label* display);
	
	template<typename T>
	void Update(Label* display, T& obj);

}}

#include <ucurses/gui/ArrayUI_def.hpp>
