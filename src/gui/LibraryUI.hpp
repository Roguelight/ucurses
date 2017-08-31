/*
 *
 *
 */

#pragma once
#include <ucurses/ucurses.hpp>
#include <ctk/storage/Library.hpp>

namespace ucurses { namespace LibraryUI {


	template<typename T>
	void Display(Window* win, ctk::Library<T>& lib);

	template<typename T>
	void Search(Window* win, ctk::Library<T>& lib);
	
	template<typename T>
	void Select(Window* win, ctk::Library<T>& lib);



}}
