/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>
#include <ctk/storage/Library.hpp>

namespace ucurses { namespace LibraryUI {


	template<typename T>
	void Display(Window* win, const ctk::Library<T>& lib, coord2d pos = coord2d(2,2));

	template<typename T>
	void Search(const ctk::Library<T>& lib, TextEntry* search, Label* display);
	
	template<typename T>
	void Select(const ctk::Library<T>& lib, Menu* select, Label* display);
	
	template<typename T>
	void Update(Label* display, T& obj);

}}
